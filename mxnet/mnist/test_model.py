#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 12 18:03:35 2018

@author: bdus
"""


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