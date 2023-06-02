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
import tensorflow as tf
import pandas as pd
from google.colab import files
import io
import numpy as np
from sklearn.preprocessing import StandardScaler

tf.random.set_seed(42)
data_train_labels_path = './data/train_labels.txt'
data_train_validation_path = './data/validation_labels.txt'
test_path = './data/sample_submission.txt'
data_train_dir = "./data"
batch_size = 100

train = np.array([(line.split(",")[0]+".png", line.split(",")[1]) for line in tf.io.read_file(data_train_labels_path).numpy().decode().split("\n")[1:-1]])
validation = np.array([(line.split(",")[0]+".png",line.split(",")[1]) for line in tf.io.read_file(data_train_validation_path).numpy().decode().split("\n")[1:-1]])
test = np.array([(line.split(",")[0]+".png", *line.split(",")[1]) for line in tf.io.read_file(test_path).numpy().decode().split("\n")[1:-1]])

data = pd.DataFrame(train, columns=['img', 'label'])
data.to_csv("data.csv")

valid_data = pd.DataFrame(validation, columns=['img', 'label'])
valid_data.to_csv("valid.csv")

test_data = pd.DataFrame(test, columns=["img", 'label'])
test_data.to_csv("test.csv")


df = pd.read_csv("./data.csv")
df['img'] = df['img'].astype('str')
df['label'] = df['label'].astype('str')

df_valid = pd.read_csv("./valid.csv")
df_valid['img'] = df_valid['img'].astype('str')
df_valid['label'] = df_valid['label'].astype('str')

df_test = pd.read_csv("./test.csv")
df_test['img'] = df_test['img'].astype('str')
df_test['label'] = df_test['label'].astype('str')
scaler = StandardScaler()

# Define a pre-processing function that normalizes the images
def preprocess_image(image):
    image = tf.image.per_image_standardization(image)
    return image
# def batch_transform(batch):
#   # Reshape the batch to 2D
#     batch = batch.reshape(batch.shape[0], -1)
#     # Scale the batch using the fitted scaler
#     batch = scaler.transform(batch)
#     # Reshape the batch back to 4D
#     batch = batch.reshape(batch.shape[0], 224, 224, 3)
#     return batch
image_gen = tf.keras.preprocessing.image.ImageDataGenerator(
    horizontal_flip=True,
    vertical_flip=True,
    rescale=1./255,
    rotation_range=20,
    shear_range=0.2,
    zoom_range=0.2,
    preprocessing_function=preprocess_image
)

image_test_gen = tf.keras.preprocessing.image.ImageDataGenerator(
    rescale=1./255
)

data_train_generator = image_gen.flow_from_dataframe(
    dataframe=df,
    directory="./data/data",
    x_col="img",
    y_col="label",
    shuffle=True,
    target_size=(224, 224),
    batch_size=batch_size,
    class_mode="binary",
    preprocessing_function=preprocess_image,

)

data_valid_generator = image_gen.flow_from_dataframe(
    dataframe=df_valid,
    directory="./data/data",
    x_col="img",
    y_col="label",
    shuffle=False,
    target_size=(224, 224),
    batch_size=batch_size,
    class_mode="binary"
)

data_test_generator = image_test_gen.flow_from_dataframe(
    dataframe=df_test,
    directory="./data/data",
    x_col="img",
    y_col="label",
    shuffle=False,
    target_size=(224, 224),
    batch_size=batch_size,
)
model = tf.keras.Sequential([
    tf.keras.layers.Conv2D(16, (3, 3), activation='relu', input_shape=(224, 224, 3)),
    tf.keras.layers.BatchNormalization(),
    tf.keras.layers.MaxPooling2D(2, 2),
    # Second Convolution
    tf.keras.layers.Conv2D(32, (3, 3), activation='relu'),
    tf.keras.layers.BatchNormalization(),
    tf.keras.layers.MaxPooling2D(2, 2),
    # Third Convolution
    tf.keras.layers.Conv2D(64, (3, 3), activation='relu'),
    tf.keras.layers.BatchNormalization(),
    tf.keras.layers.MaxPooling2D(2, 2),
    # Flatten
    tf.keras.layers.Flatten(),
    # Dense layer
    # tf.keras.layers.Dense(512, activation='relu'),
    # tf.keras.layers.Dense(60, activation='relu'),
    # tf.keras.layers.Dense(30, activation='relu'),
    tf.keras.layers.Dense(512, activation='relu'),
    tf.keras.layers.Dropout(0.5),
    tf.keras.layers.Dense(256, activation='relu'),
    tf.keras.layers.Dropout(0.5),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dropout(0.5),
    tf.keras.layers.Dense(1, activation='sigmoid')
])
from keras import backend as K
from sklearn.metrics import accuracy_score
from sklearn.metrics import precision_score
from sklearn.metrics import recall_score
from sklearn.metrics import f1_score

model.compile(loss=tf.keras.losses.binary_crossentropy,
              optimizer=tf.keras.optimizers.Adam(learning_rate=0.01),
              metrics=["accuracy"])

history = model.fit(data_train_generator, 
                    validation_data=data_valid_generator,
                    epochs=5)
# predict probabilities for test set
y_pred = model.predict(data_test_generator, verbose=0)
# Getting the accuracy and loss
acc = history.history['accuracy']
# val_acc = history.history['val_accuracy']
loss = history.history['loss']
# val_loss = history.history['val_loss']
acc, loss


# y_pred = (model.predict(data_valid_generator) > 0.5).astype("int32")
y_classes = (y_pred > 0.5).astype("int32")

# validation_labels = validation_labels[:,1].astype("int32")
y_classes = np.concatenate(y_classes, axis=0)

test_labels = test[:,1].astype("int32")
# accuracy: (tp + tn) / (p + n)
accuracy = accuracy_score(test_labels, y_classes)


# precision tp / (tp + fp)

precision = precision_score(test_labels, y_classes)


# recall: tp / (tp + fn)

recall = recall_score(test_labels, y_classes)


# f1: 2 tp / (2 tp + fp + fn)

f1 = f1_score(test_labels, y_classes)

print(f1)
import csv

filename = "submission.csv"
fields = ["id", "class"]

test_ids = np.array([(line.split(",")[0]) for line in tf.io.read_file(test_path).numpy().decode().split("\n")[1:-1]])

print(np.shape(test_ids))
print(y_classes)
with open(filename, 'w', newline='') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=fields)

    writer.writeheader()

    for i in range(len(test_ids)):
      row = { "id": test_ids[i], "class": y_classes[i].astype("str")}
      writer.writerow(row)

print(len(test_ids))
from sklearn.metrics import confusion_matrix
print(confusion_matrix(test_labels, y_classes), ": is the confusion matrix")
from sklearn.metrics import accuracy_score
print(accuracy_score(test_labels, y_classes), ": is the accuracy score")
from sklearn.metrics import precision_score
print(precision_score(test_labels, y_classes), ": is the precision score")
from sklearn.metrics import recall_score
print(recall_score(test_labels, y_classes), ": is the recall score")
from sklearn.metrics import f1_score
print(f1_score(test_labels, y_classes, labels=np.unique(test_labels)), ": is the f1 score")