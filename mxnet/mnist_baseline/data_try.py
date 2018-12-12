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
import get_data

from mxnet import autograd, gluon, init, nd
from mxnet.gluon import nn, loss as gloss


num_epochs = 5
batch_size = 100

# get data csv
mnistcsv = get_data.read(one_hot=False)

# network
net = nn.Sequential()
net.add(
        nn.Dense(10)
        )
net.initialize(mx.init.Xavier(magnitude=2.24))
loss = gloss.SoftmaxCrossEntropyLoss()
trainer = gluon.Trainer(net.collect_params(),'sgd',{'learning_rate':0.1})
metric = mx.metric.Accuracy()


# train
def train(epochs):
    for epoch in range(num_epochs):
        metric.reset()
        for i in range(1000):
            train_l_sum = 0
            train_acc_sum = 0
            
            X,y = mnistcsv.train.next_batch(batch_size)
            X,y = nd.array(X), nd.array(y)
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
        
                
train(num_epochs)