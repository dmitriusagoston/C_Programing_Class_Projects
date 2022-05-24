from typing import List, Tuple

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from tqdm.notebook import trange

import random
seed = 2001
random.seed(seed)
np.random.seed(seed)

# Load data
def load_data():
    data = pd.read_csv("./song_data.csv", index_col=0).drop(["song_name"], axis = 1)
    return data

# Visualize data 
def vis_data():
    data.info()
    data.hist(figsize=(14,14))

# Clean data
def clean_data(data):
    # drop rows that have NULL value
    data = data.dropna()

    # Remove outliers
    for feature in ['song_duration_ms', 'instrumentalness']:
        q1 = data[feature].quantile(q=0.25)
        q3 = data[feature].quantile(q=0.75)
        iqr = q3 - q1
        a = q1 - (iqr * 1.5)
        b = q3 + (iqr * 1.5)
        data = data[(data[feature] >= a) & (data[feature] <= b)]
    data = data.reset_index(drop=True)

    # Scale with z score normilization
    for feature in data:
        if feature == "song_popularity":
            continue
        mean = data[feature].mean()
        std = data[feature].std()
        data[feature] = (data[feature] - mean) / std
        mean = data[feature].mean()
        std = data[feature].std()
    data["song_popularity"] = data["song_popularity"] / 100
    return data

# Dataset preperation: creation of test set and train/validation set
def test_split(data, test_size: float=0.3, seed=seed):
    X = data.iloc[:,:-1]
    y = data['song_popularity']
    X_train_val, X_test, y_train_val, y_test = train_test_split(X, y, test_size=test_size, random_state=seed)
    
    return (X_train_val.reset_index(drop=True),
            y_train_val.reset_index(drop=True),
            X_test.reset_index(drop=True),
            y_test.reset_index(drop=True))

# Dataset preperation: split train/validation set
def train_val_split(X_train_val, y_train_val, k=5, seed=seed):
    index_shuffle = list(X_train_val.index)
    random.shuffle(index_shuffle)
    index_split_list = [[index_shuffle[i+j] for i in range(0, len(index_shuffle), 5)  if i+j<len(index_shuffle)] for j in range(5)]
    train_val_pairs = [(None, None, None, None) for _ in range(k)]

    indexy = list(y_train_val.index)
    indexy = [[indexy[i+j] for i in range(0, len(indexy), 5)  if i+j<len(indexy)] for j in range(5)]
    for i in range(k):
        val_foldx = index_split_list[i]
        val_foldy = indexy[i]
        train_foldx = []
        train_foldy = []
        for j in range(k):
          if j != i:
            train_foldx.extend(index_split_list[j])
            train_foldy.extend(indexy[j])
        train_val_pairs[i] = (train_foldx, train_foldy, val_foldx, val_foldy)
    return train_val_pairs


data = load_data()
vis_data()
data = clean_data(data)
vis_data()

X_train_val, y_train_val, X_test, y_test = test_split(data)
train_val_pairs = train_val_split(X_train_val, y_train_val)

# Calculate MSE Loss
def MSE_loss(pred: np.ndarray, target: np.ndarray):
    se = (pred - target) ** 2
    sse = np.sum(se)
    l = sse / target.size
    l /= 2
    return l

# Gradient descent step
def gradient(X: np.ndarray, y: np.ndarray, theta: np.ndarray):
    m = len(y)
    J = 0
    h_x = np.dot(X, theta)
    et = sum((h_x - y)**2)
    l = et/(2*m)
    return l

# Specify epoch and learning rate
num_epochs = 25
learning_rate = 0.1
k = 5
train_loss_history = [[] for _ in range(k)]
val_loss_history = [[] for _ in range(k)]

theta_min = None
index_min = None
loss_min = None

for i in range(k):
    X_train, y_train, X_val, y_val = train_val_pairs[i]
    Xt = pd.DataFrame(data, index=X_train)
    Xt = Xt.iloc[:,:-1]
    Xv = pd.DataFrame(data, index=X_val)
    Xv = Xv.iloc[:,:-1]
    yt = pd.DataFrame(data, index=y_train)
    yt = yt.iloc[:,:1]
    yv = pd.DataFrame(data, index=y_val)
    yv = yv.iloc[:,:1]
    Xt = Xt.to_numpy()
    Xv = Xv.to_numpy()
    yt = yt.to_numpy()
    yv = yv.to_numpy()
    Xtr, Xtc = Xt.shape
    Xvr, Xvc = Xv.shape
    Xt = np.concatenate((np.ones((Xtr, 1)), Xt), axis=1)
    Xv = np.concatenate((np.ones((Xvr, 1)), Xv), axis=1)
    
    # Initialize theta    
    theta = np.zeros(13)
    
    for epoch in trange(num_epochs, desc="Epoch"):
        # Compute loss, and save to train_loss_history and val_loss_history
        predt = Xt.dot(theta)
        predv = Xv.dot(theta)
        losst = MSE_loss(predt, yt)
        lossv = MSE_loss(predv, yv)
        train_loss_history[i].append(losst)
        val_loss_history[i].append(lossv)
        
        # Update parameter
        m = yt.size
        temp = theta - (learning_rate * (1/m) * ((np.transpose(Xt @ theta) - np.transpose(yt)) @ Xt))
        lcv = 0
        for t in temp[0]:
            theta[lcv] = t
            lcv += 1
  
    # Inference on validation set, and find the best parameters. Save corresponding parameters and index in theta_min and  index_min
    predv = Xv.dot(theta)
    lossv = MSE_loss(predv, yv)
    if (loss_min is None or lossv < loss_min):
      loss_min = lossv
      theta_min = theta
      index_min = i

print(f"Final train loss for the best model: {train_loss_history[index_min][-1]}")
print(f"Final validation loss for the best model: {val_loss_history[index_min][-1]}")
print("Parameters for the best model: ", theta_min)

plt.plot(np.arange(num_epochs), train_loss_history[index_min], label="Train loss")
plt.plot(np.arange(num_epochs), val_loss_history[index_min], label="Val loss")
plt.title("Train + validation loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend()
plt.show()


# Evaluate on test set
Xt = X_test
Xt = Xt.to_numpy()
Xtr, Xtc = Xt.shape
Xt = np.concatenate((np.ones((Xtr, 1)), Xt), axis=1)
yt = y_test
yt = yt.to_numpy()
predt = Xt.dot(theta_min)
losst = MSE_loss(predt, yt)
test_loss = losst            
print(f"Test loss: {test_loss}")