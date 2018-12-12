# mnist
csv格式MNIST数据gluon分类demo
    https://www.kaggle.com/c/digit-recognizer

CSV文件有两个,分别是有标记集train.csv和无标记集合test.csv

## mxnet.gluon.data.dataset

读取数据继承自官方[Dataset](https://mxnet.incubator.apache.org/_modules/mxnet/gluon/data/dataset.html#Dataset)
仿照官方[MNIST](https://mxnet.incubator.apache.org/_modules/mxnet/gluon/data/vision/datasets.html#MNIST)源代码写

使用pandas库读取csv文件:

### 核心代码

```python
import os
import sys
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder

TRAIN_DATA = 'train.csv'
_TEST_DATA = 'test.csv'
filenames =  [os.path.join(data_dir_,x) for x in [_TRAIN_DATA,_TEST_DATA]]

# get images and labels
labeled_images = pd.read_csv(filenames[0])
validation_images = pd.read_csv(filenames[1])
#
_length = labeled_images.shape[0]
images = labeled_images.iloc[0:_length ,1:] #1:784
labels = labeled_images.iloc[0:_length ,:1] #0:1
images = np.array(images,dtype=dtype)
labels = np.array(labels,dtype=dtype)

train_images, test_images,train_labels, test_labels = train_test_split(images, labels, train_size=0.8, random_state=0)

_length = validation_images.shape[0]
vali_images = labeled_images.iloc[0:_length ,:]
vali_images = np.array(vali_images,dtype=dtype)
```

### 完整代码

MNISTcsv.py

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 22 22:03:58 2018
@author: bdus

@description:
仿照官方[MNIST](https://mxnet.incubator.apache.org/_modules/mxnet/gluon/data/vision/datasets.html#MNIST)源代码写的csvMNIST
主要是为了熟悉gluon的dataset
"""
import os
import sys
import numpy as np
import mxnet as mx
import pandas as pd

from mxnet.gluon.data import dataset
from sklearn.preprocessing import OneHotEncoder
from sklearn.model_selection import train_test_split


class MNIST_csv(dataset._DownloadedDataset):
    """
    @Description
        create MNIST dataset from csv files.
        https://www.kaggle.com/c/digit-recognizer
    
    @base model 
        mxnet.gluon.data.dataset.Dataset        
        detailed:
        https://mxnet.incubator.apache.org/_modules/mxnet/gluon/data/dataset.html#Dataset
        
    
    """
    def __init__(dasein,data_dir_=os.path.join('./data','csvMNIST'),train=True,one_hot=False,transform=None):        
        dasein.one_hot = one_hot
        dasein._TRAIN_DATA = 'train.csv'
        dasein._TEST_DATA = 'test.csv'
        
        dasein._one_hot = one_hot
        dasein.data_dir_ = data_dir_
        dasein._train = train
        dasein.transform = transform
        dasein.dtype = np.float32
            
        dasein._epochs_completed = 0
        dasein._index_in_epoch = 0 
        super(MNIST_csv,dasein).__init__(data_dir_,transform) 
        
    def _get_data(dasein):
    """
    这个函数是因为该类继承于_DownloadedDataset[link](https://mxnet.incubator.apache.org/_modules/mxnet/gluon/data/dataset.html#Dataset)
    执行super(MNIST_csv,dasein).__init__(data_dir_,transform) 的时候
     会将data和label初始化在
     self._data = None 
      和
     self._label = None
      中
     
    """        
        filenames =  [os.path.join(dasein.data_dir_,x) for x in [dasein._TRAIN_DATA,dasein._TEST_DATA]]
            
        filename = filenames[0]
        
        # get images and labels
        labeled_images = pd.read_csv(filename)     
        
        #
        _length = labeled_images.shape[0]
        images = labeled_images.iloc[0:_length ,1:]
        labels = labeled_images.iloc[0:_length ,:1]
        images = np.array(images,dtype=dasein.dtype)
        labels = np.array(labels,dtype=dasein.dtype)
        
        # load data end           
        assert images.shape[0] == labels.shape[0]
        
        train_images, test_images,train_labels, test_labels = train_test_split(images, labels, train_size=0.8, random_state=0)
        
        
        if dasein._train:
            images,labels = train_images, train_labels
        else:
            images,labels = test_images, test_labels
        
        
        # image                
        dasein._num_examples = images.shape[0]
        dasein._data = np.multiply(images,1.0/255.0)
        
        
        # label
        if True == dasein._one_hot:
            """
            def dense_to_onehot():
            https://www.cnblogs.com/wxshi/p/8645600.html
            https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.OneHotEncoder.html    
            """    
            dasein.enc = OneHotEncoder(categories='auto')
            dasein.enc.fit(labels)
            dasein._label = mx.nd.array(dasein.enc.transform(labels).toarray(),dtype=dasein.dtype)
        else:
            dasein._label = mx.nd.array(labels,dtype=dasein.dtype)
    
```
## gluon.data.DataLoader


```python
mnist_train = MNIST_csv(train=True)
mnist_val = MNIST_csv(train=False)

train_data = gluon.data.DataLoader(dataset=mnist_train, batch_size=100,shuffle=True,last_batch='discard')
val_data = gluon.data.DataLoader(dataset=mnist_val, batch_size=100,shuffle=False)

```

## train model

### softmax.py

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Nov 23 12:51:12 2018

@author: bdus

https://github.com/apache/incubator-mxnet/blob/master/example/gluon/mnist/mnist.py
"""

import mxnet as mx
import numpy as np
import matplotlib.pyplot as plt
from MNISTcsv import MNIST_csv

from mxnet import autograd, gluon, init, nd
from mxnet.gluon import nn, loss as gloss


batch_size = 100

# get data csv
mnist_train = MNIST_csv(train=True)
mnist_val = MNIST_csv(train=False)

train_data = gluon.data.DataLoader(dataset=mnist_train, batch_size=100,shuffle=True,last_batch='discard')
val_data = gluon.data.DataLoader(dataset=mnist_val, batch_size=100,shuffle=False)


# network
net = nn.Sequential()
net.add(
        nn.Dense(10)
        )

loss = gloss.SoftmaxCrossEntropyLoss()
metric = mx.metric.Accuracy()
# train
def test():
    metric = mx.metric.Accuracy()
    for data, label in val_data:        
        output = net(data)
        metric.update([label], [output])
    return metric.get()
       
def train(epochs):
    net.initialize(mx.init.Xavier(magnitude=2.24))
    trainer = gluon.Trainer(net.collect_params(),'sgd',{'learning_rate':0.1})
    
    for epoch in range(epochs):
        metric.reset()
        for i, (X, y) in enumerate(train_data):
            #X = nd.array(X)
            #y = nd.array(y)
            with autograd.record():
                output = net(X)
                L = loss(output,y)
                L.backward()
            trainer.step(batch_size)
            metric.update(y,output)            
            if i % 50 == 0:
                name, acc = metric.get()
                print('[Epoch %d Batch %d] Training: %s=%f'%(epoch, i, name, acc))
        name, acc = metric.get()
        print('[Epoch %d] Training: %s=%f'%(epoch, name, acc))
        name, val_acc = test()
        print('[Epoch %d] Validation: %s=%f'%(epoch, name, val_acc))
    net.save_parameters('mnist.params') 

if __name__ == '__main__':
    num_epochs = 5
    train(num_epochs)
```
### test

```python
import mxnet as mx
import numpy as np
import matplotlib.pyplot as plt
import get_data

from mxnet import autograd, gluon, init, nd
from mxnet.gluon import nn, loss as gloss

batch_size = 1
num_test_images = 10# 

# get data csv
mnistcsv = get_data.read(one_hot=True)

# get model

net = nn.Sequential()
net.add(
        nn.Dense(10)
        )

net.load_parameters('mnist.params')

for i in range(num_test_images):
    X,_ = mnistcsv.validation.next_batch(batch_size)
    X = nd.array(X)
    y = net(X)
    ans = y.argmax(axis=1).asnumpy()        
    print("%d-th type %d" % (i, ans))   

# ===================== ====================
img_data = nd.array(mnistcsv.validation.data)
y = net(img_data)
Label = y.argmax(axis=1).asnumpy().astype(np.int8)
Image = np.arange(len(Label)) +1
dataframe = pd.DataFrame({'ImageId':Image,'Label':Label})
dataframe.to_csv("myout.csv",index=False,sep=',')

```

![](./img/first_submit.png)