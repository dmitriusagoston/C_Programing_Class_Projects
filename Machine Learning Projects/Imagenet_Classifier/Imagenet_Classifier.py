# Ignore the warnings - Otherwise, TensorFlow tends to innundate one with far too many warnings.
import warnings
warnings.filterwarnings('always')
warnings.filterwarnings('ignore')

# Data visualizaton.
import matplotlib.pyplot as plt
from matplotlib import style
import seaborn as sns
import random as rn

# Configure some defaults.
style.use('fivethirtyeight')
sns.set(style='whitegrid',color_codes=True)

# ML + Deep Learning Imports
import tensorflow as tf
from keras import backend as k
from tensorflow import keras
from keras.regularizers import l2
from keras.preprocessing.image import ImageDataGenerator # Data Augmentation
from tensorflow.keras import regularizers 
from tensorflow.keras.models import Sequential # This building the models
from tensorflow.keras.layers import Dense, Dropout, Flatten, Activation, Conv2D, MaxPooling2D, BatchNormalization 
from tensorflow.keras.optimizers import Adam, SGD, Adagrad, Adadelta, RMSprop 
from tensorflow.keras.utils import to_categorical # if label is 0,1,...,99 etc then it becomes [0,...1,.,0] a len 100 vector
from keras.callbacks import ReduceLROnPlateau #learning rate decay policy
from sklearn.model_selection import train_test_split # for splitting data

from tensorflow.keras.layers import Input
from tensorflow.keras.applications.vgg16 import VGG16, preprocess_input
from tensorflow.keras.applications.efficientnet_v2 import EfficientNetV2S, preprocess_input
from tensorflow.keras.applications.densenet import DenseNet201, preprocess_input
from tensorflow.keras.preprocessing import image
from tensorflow.keras.models import Model

import numpy as np
import pandas as pd # for making our csv
import time
# Image preprocessing and reading in.
import imageio 
from pathlib import Path
import os, sys
from zipfile import ZipFile

path = 'tiny-image-net-100/'

def get_id_dictionary():
  """
  Maps each class id to an unique integer.
  """
  id_dict = {}
  for i, line in enumerate(open( path + 'wnids.txt', 'r')):
      id_dict[line.replace('\n', '')] = i
  return id_dict
  
def get_class_to_id_dict():
  """
  Maps each class id to the English version of the label.
  """
  id_dict = get_id_dictionary()
  all_classes = {}
  result = {}
  for i, line in enumerate(open( path + 'words.txt', 'r')):
      n_id, word = line.split('\t')[:2]
      all_classes[n_id] = word
  for key, value in id_dict.items():
      result[value] = (key, all_classes[key])      
  return result

def get_data(id_dict, n_samples=10):
    """
    n_samples: number of samples per class. n_samples has a max of 500.
    The range is [1, 500].
    """
    print('starting loading data')
    train_data, test_data = [], []
    train_labels = []
    t = time.time()
    for key, value in id_dict.items():
      if value<100: # Only focus on first 100 classes
        train_data += [imageio.imread( path + 'train/{}/images/{}_{}.JPEG'.format(key, key, str(i)), pilmode='RGB') for i in range(n_samples)]
        train_labels_ = np.array([[0]*100]*n_samples)
        train_labels_[:, value] = 1
        train_labels += train_labels_.tolist()

    test_image_names = []
    path_list = list(Path(path+'test/images/').glob('*.jpg'))
    for test_image_path in path_list:
        img_name = str(test_image_path).split('.')[0][-18:]
        test_image_names.append(img_name)
        test_data.append(imageio.imread(test_image_path , pilmode='RGB'))
        
    print('finished loading data, in {} seconds'.format(time.time() - t))
    return np.array(train_data), np.array(train_labels), np.array(test_data), test_image_names

# Data Prep
id_dict = get_id_dictionary()
class_to_id_dict = get_class_to_id_dict()
train_data, train_labels, x_test, y_test = get_data(id_dict, 500)
x_train, x_val, y_train, y_val = train_test_split(train_data, train_labels, test_size=0.3)
x_test_names = y_test

print( "train data shape: ",  x_train.shape )
print( "train label shape: ", y_train.shape )
print( "val data shape: ",  x_val.shape )
print( "val label shape: ", y_val.shape )
print( "test data shape: ",   x_test.shape )

# Set up data generators for training and validation set
# add transformations

datagen = ImageDataGenerator(
          rescale=1/255.,
          featurewise_center=False,           # set input mean to 0 over the dataset
          samplewise_center=False,            # set each sample mean to 0
          featurewise_std_normalization=False,# divide inputs by std of the dataset
          samplewise_std_normalization=False, # divide each input by its std
          zca_whitening=False,                # apply ZCA whitening
          rotation_range=0,                   # randomly rotate images in the range (degrees, 0 to 180)
          width_shift_range=0.1,              # randomly shift images horizontally (fraction of total width)
          height_shift_range=0.1,             # randomly shift images vertically (fraction of total height)
          horizontal_flip=True,               # randomly flip images
          vertical_flip=True)                 # randomly flip images


# Data generators creation

valid_datagen = ImageDataGenerator(rescale=1/255.)

datagen.fit(x_train, augment=True)
traingen = datagen.flow(x_train, y_train, batch_size=200)

valid_datagen.fit(x_val)
valgen = valid_datagen.flow(x_val, y_val, batch_size=200)

# Model creation

base_model = DenseNet201(weights = 'imagenet', 
                              include_top = False, 
                              input_shape = (64, 64, 3),
                              pooling = None)

x = base_model.output
x = Flatten()(x)
x = Dense(1024, activation = 'relu')(x)
x = Dropout(0.8)(x)
predic = Dense(100, activation = 'softmax')(x) 
model = Model(inputs = base_model.input, outputs = predic) 

# Compile model

lr_reducer = ReduceLROnPlateau(factor=np.sqrt(0.1), cooldown=0, patience=5, min_lr=0.5e-3)
model.compile(optimizer = Adam(0.0001),
              loss = 'categorical_crossentropy', 
              metrics = ['accuracy'])

# Train

def setseeds():
  np.random.seed(720)
  rn.seed(720)
  tf.random.set_seed(720)

setseeds()

nb_epoch = 20
batch_size = 200
# Fit the model on the batches generated by datagen.flow().
history = model.fit_generator(traingen, epochs=nb_epoch, validation_data=valgen) # fit model using fit_generator

# Plotting results

# Plot Model Performance
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Model Loss')
plt.ylabel('Loss')
plt.xlabel('Epochs')
plt.legend(['train', 'test'])
plt.show()

plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('Model Accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epochs')
plt.legend(['train', 'test'])
plt.show()