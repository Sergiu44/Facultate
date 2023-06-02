import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import tensorflow as tf
import csv

import os
import json
from pathlib import Path

api_key = {"username":"sergiustanciunicolas","key":"e52e3b4c5322a499dc2c011e70b295ec"}
kaggle_path = Path('/root/.kaggle')
os.makedirs(kaggle_path, exist_ok=True)

with open (kaggle_path/'kaggle.json', 'w') as handl:
    json.dump(api_key,handl)

os.chmod(kaggle_path/'kaggle.json', 600)

!kaggle competitions download -c unibuc-brain-ad
!unzip unibuc-brain-ad.zip

data_train_labels_path = './data/train_labels.txt'
data_train_validation_path = './data/validation_labels.txt'
test_path= './data/sample_submission.txt'

train = np.array([(line.split(",")[0]+".png", *line.split(",")[1]) for line in tf.io.read_file(data_train_labels_path).numpy().decode().split("\n")[1:-1]])
validation = np.array([(line.split(",")[0]+".png", *line.split(",")[1]) for line in tf.io.read_file(data_train_validation_path).numpy().decode().split("\n")[1:-1]])
test = np.array([(line.split(",")[0]+".png", *line.split(",")[1]) for line in tf.io.read_file(test_path).numpy().decode().split("\n")[1:-1]])

data = pd.DataFrame(np.concatenate((train, validation), axis=0), columns=['img', 'label'])
data.to_csv("data.csv")

df = pd.read_csv("./data.csv")
df["img"] = df['img'].astype('str')
df["label"] = df['label'].astype('str')


tf.random.set_seed(42)

data_train_dir = "./data"

train_data_gen = tf.keras.preprocessing.image.ImageDataGenerator()

data_train_generator = train_data_gen.flow_from_dataframe(
    dataframe=df,
    directory="./data/data",
    x_col="img",
    y_col="label",
    shuffle=True,
    batch_size=100,
    target_size=(224, 224),
    class_mode="binary"
)

from sklearn.naive_bayes import GaussianNB
from sklearn.preprocessing import StandardScaler

scalar = StandardScaler()
nbModel = GaussianNB()

# Get the number of batches
num_batches = len(data_train_generator)

# Train the model on each batch
for i in range(num_batches):
    batch_x, batch_y = data_train_generator[i]
    # Reshape the batch of images to 2D array
    batch_x = batch_x.reshape((batch_x.shape[0], -1))
    # Normalized batch of image
    batch_x_normalized = scalar.fit_transform(batch_x)
    # Fit the model on the batch
    nbModel.partial_fit(batch_x_normalized, batch_y, classes=[0,1])


data = pd.DataFrame(test, columns=['img', 'label'])
data.to_csv("test.csv")

df = pd.read_csv("./test.csv")
df["img"] = df['img'].astype('str')
df["label"] = df['label'].astype('str')

test_data_gen = tf.keras.preprocessing.image.ImageDataGenerator()

test_data_gen = test_data_gen.flow_from_dataframe(
    dataframe=df,
    directory="./data/data",
    x_col="img",
    y_col="label",
    shuffle=False,
    batch_size=100,
    target_size=(224, 224),
)


num_batches = len(test_data_gen)

y_pred, test_labels = [], []

for i in range(num_batches):
  batch_x, batch_y = test_data_gen[i]
  # Reshape the batch of images to 2D array
  batch_x = batch_x.reshape((batch_x.shape[0], -1))
  # Normalize batch of images
  batch_x_normalized = scalar.fit_transform(batch_x)
  # Make predictions on the batch
  batch_y_pred = nbModel.predict(batch_x_normalized)
  y_pred.append(batch_y_pred)
  test_labels.append(batch_y)

y_pred = np.concatenate(y_pred, axis=0)
test_labels = np.concatenate(test_labels, axis=0)


filename = "submission.csv"
fields = ["id", "class"]

test_ids = np.array([(line.split(",")[0]) for line in tf.io.read_file(test_path).numpy().decode().split("\n")[1:-1]])

print(test_ids)
print(y_pred)
with open(filename, 'w', newline='') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=fields)

    writer.writeheader()

    for i in range(len(test_ids)):
      row = { "id": test_ids[i], "class": y_pred[i].astype("str")}
      writer.writerow(row)

print(len(test_ids))



validation_labels = validation[:,1].astype(int)

from sklearn.metrics import confusion_matrix
print(confusion_matrix(validation_labels, y_pred), ": is the confusion matrix")
from sklearn.metrics import accuracy_score
print(accuracy_score(validation_labels, y_pred), ": is the accuracy score")
from sklearn.metrics import precision_score
print(precision_score(validation_labels, y_pred), ": is the precision score")
from sklearn.metrics import recall_score
print(recall_score(validation_labels, y_pred), ": is the recall score")
from sklearn.metrics import f1_score
print(f1_score(validation_labels, y_pred, labels=np.unique(validation_labels)), ": is the f1 score")