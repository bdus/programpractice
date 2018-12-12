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