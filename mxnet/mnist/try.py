"""
https://www.kaggle.com/

digital number recognation

"""
import numpy as np
import pandas as pd
import mxnet as mx

import os
print(os.listdir("./data"))

labeled_images = pd.read_csv("./data/train.csv")

images = labeled_images.iloc[0:5000,1:]
labels = labeled_images.iloc[0:5000,:1]

from sklearn.model_selection import train_test_split
train_images, test_images,train_labels, test_labels = train_test_split(images, labels, train_size=0.8, random_state=0)

import matplotlib.pyplot as plt, matplotlib.image as mpimg
i=1
img=train_images.iloc[i].as_matrix()
img=img.reshape((28,28))
plt.imshow(img,cmap='gray')
plt.title(train_labels.iloc[i,0])
plt.show()

from sklearn import svm

clf = svm.SVC()
clf.fit(train_images, train_labels.values.ravel())
clf.score(test_images,test_labels)

test_images[test_images>0]=1
train_images[train_images>0]=1

clf = svm.SVC()
clf.fit(train_images, train_labels.values.ravel())
clf.score(test_images,test_labels)

test_data=pd.read_csv('../input/test.csv')
test_data[test_data>0]=1
results=clf.predict(test_data[0:5000])
results
df = pd.DataFrame(results)
df.index.name='ImageId'
df.index+=1
df.columns=['Label']
df.to_csv('results.csv', header=True)