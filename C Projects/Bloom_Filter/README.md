# asignment 7
The purpose of this program is to first create a Bloom filter with a corresponding hash table. This Bloom filter and hash table is responsible for taking in words that are designated as badspeak. The program will then read in a list of words that are formatted in pairs for oldspeak and the corresponding newspeak. Though only the oldspeak will be added to the Bloom filter while both new and oldspeak will be added to the hash table. The program can then take in an input and filter out the desired words from the given input. While parsing through the input if a word found is also in the Bloom filter there will be three choices of actions to take from this point. One being there is no translation and the user of the input is “guilty”. Second being there is a translation and they are deemed needing “counselling”. Third is the possibility of a false positive. If either of the first two cases are found true there are two separate messages to be given for each corresponding case. In both cases the user will be notified of the words caught by the Bloom filter.


# building
To build this program:
- clone this repo
- cd into cse13s/asgn7/
- make

# running
To run this program:

USAGE
./banhammer [-hs] [-t size] [-f size]

OPTIONS
- -h             Program usage and help.
- -s             Orint program statistics.
- -t size        Specify hash table size (default: 2^16).
- -f size        Specify Bloom filter size (default: 2^20).
