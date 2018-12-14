#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec 14 09:29:43 2018

@author: bdus

baseline:
https://github.com/bdus/programpractice/blob/master/mxnet/mnist_baseline/softmax.py

Temporal_Ensembling_for_Semi-supervised_Learning
$\pi$ model
"""

import _init_paths

import os
import mxnet as mx
import numpy as np
#import matplotlib.pyplot as plt
#from dataset.MNISTcsv import MNIST_csv
from gluoncv import model_zoo as mzoo

from mxnet import autograd, gluon, init, nd
from mxnet.gluon import nn, loss as gloss

from symbols import symbols

batch_size = 100
stochastic_ratio = 0.01

ctx = mx.cpu() #[mx.gpu(i) for i in range(num_gpus)] if num_gpus > 0 else [mx.cpu()]

# get data csv
transform=lambda data, label: (data.reshape(784,).astype(np.float32)/255, label)
train_data = gluon.data.DataLoader(dataset= gluon.data.vision.MNIST(train=True,transform=transform), batch_size=100,shuffle=True,last_batch='discard')
val_data = gluon.data.DataLoader(dataset= gluon.data.vision.MNIST(train=False,transform=transform), batch_size=100,shuffle=False)

# network
modelname = 'semi_pi_simple2'
basemodel_zoo = 'simple2'
net = symbols.get_model('simple2')
net.initialize(mx.init.Xavier(magnitude=2.24))
#net.load_parameters(os.path.join('symbols','para','%s.params'%(modelname)))

# g(x) : stochastic input augmentation function
def g(x):
    return x + nd.random.normal(0,stochastic_ratio,shape=x.shape)

# loss function
l_logistic = gloss.SoftmaxCrossEntropyLoss()
l_l2loss = gloss.L2Loss() 
metric = mx.metric.Accuracy()
# train
def test():
    metric = mx.metric.Accuracy()
    for data, label in val_data:
        X = data.reshape((-1,1,28,28))
        #img = nd.concat(X,X,X,dim=1)
        output = net(X)
        metric.update([label], [output])
    return metric.get()
       
def train(epochs,alpha):    
    #net.initialize(mx.init.Xavier(magnitude=2.24))
    trainer = gluon.Trainer(net.collect_params(),'sgd',{'learning_rate':0.1})
    
    for epoch in range(epochs):
        metric.reset()
        for i, (X, y) in enumerate(train_data):
            X = nd.array(X)
            X = X.reshape((-1,1,28,28))            
            y = nd.array(y)
            #y = nd.one_hot(y,10)
            with autograd.record():
                output = net(g(X))
                y2 = net(g(X))
                L = l_logistic(output,y) + alpha * l_l2loss(y1,y2) 
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
        if epoch % 10 == 0:
            net.save_parameters( os.path.join('symbols','para','%s.params'%(modelname)) )
    net.save_parameters( os.path.join('symbols','para','%s.params'%(modelname)) )

if __name__ == '__main__':
    num_epochs = 10
    alpha = 0
    train(20,0)
    for i in range(10):
        train(10,0.1*i)
    train(100,1)
    