#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 12 21:15:19 2018

@author: bdus

baseline:
https://github.com/bdus/programpractice/blob/master/mxnet/mnist_baseline/softmax.py
"""
import _init_paths

import os
import mxnet as mx
import numpy as np
import matplotlib.pyplot as plt
from dataset.MNISTcsv import MNIST_csv


from mxnet import autograd, gluon, init, nd
from mxnet.gluon import nn, loss as gloss

from symbols import symbols

batch_size = 100

# get data csv
#mnist_train = MNIST_csv(train=True)
#mnist_val = MNIST_csv(train=False)
#train_data = gluon.data.DataLoader(dataset=mnist_train, batch_size=100,shuffle=True,last_batch='discard')
#val_data = gluon.data.DataLoader(dataset=mnist_val, batch_size=100,shuffle=False)

transform=lambda data, label: (data.reshape(784,).astype(np.float32)/255, label)
train_data = gluon.data.DataLoader(dataset= gluon.data.vision.MNIST(train=True,transform=transform), batch_size=100,shuffle=True,last_batch='discard')
val_data = gluon.data.DataLoader(dataset= gluon.data.vision.MNIST(train=False,transform=transform), batch_size=100,shuffle=False)


# network
net = symbols.get_model('simple0')

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
            X = nd.array(X)
            y = nd.array(y)
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
    net.save_parameters(os.path.join('symbols','para','simple0_fm.params') )

if __name__ == '__main__':
    num_epochs = 10
    train(num_epochs)