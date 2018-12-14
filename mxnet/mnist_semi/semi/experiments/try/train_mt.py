#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec 14 12:46:58 2018

@author: bdus

baseline:
https://github.com/bdus/programpractice/blob/master/mxnet/mnist_semi/supervised/experiments/finetune/train_finetune.py

mean teacher are better role model

"""


import _init_paths

import os
import mxnet as mx
import numpy as np
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
modelname = 'semi_mt_simple2'

basemodel_zoo = 'simple2'
net_s = symbols.get_model(basemodel_zoo)
net_t = symbols.get_model(basemodel_zoo)
#net_s.initialize(mx.init.Xavier(magnitude=2.24))
#net_t.initialize(mx.init.Xavier(magnitude=2.24))
net_t.load_parameters( os.path.join('symbols','para','%s_t.params'%(modelname)) )
net_s.load_parameters( os.path.join('symbols','para','%s_s.params'%(modelname)) )

#net.load_parameters(os.path.join('symbols','para','%s.params'%(modelname)))

# g(x) : stochastic input augmentation function
def g(x):
    return x + nd.random.normal(0,stochastic_ratio,shape=x.shape)


# loss function
l_logistic = gloss.SoftmaxCrossEntropyLoss()
l_l2loss = gloss.L2Loss() 
metric = mx.metric.Accuracy()

def net_liner(net,net2,x1,x2,b):
    # net.para = x1 * net2.para + x2 * net.para + b
    for (k, v) , (k2, v2) in zip( net.collect_params().items() , net2.collect_params().items() ):
        v.set_data(v2.data() * x1 + v.data() * x2 + b)
    
# train
def test():
    metric = mx.metric.Accuracy()
    for data, label in val_data:
        X = data.reshape((-1,1,28,28))
        #img = nd.concat(X,X,X,dim=1)
        output = net_t(X)
        metric.update([label], [output])
    return metric.get()
    
def train(epochs,alpha=0,beta=0,lr=0.1):
    #net.initialize(mx.init.Xavier(magnitude=2.24))
    print('ems_alpha = %f, consis_beta = %f ,lr = %f'%(alpha,beta,lr))
    trainer = gluon.Trainer(net_s.collect_params(),'sgd',{'learning_rate':lr})
    for epoch in range(epochs):
        metric.reset()
        for i, (X, y) in enumerate(train_data):
            X = nd.array(X)
            X = X.reshape((-1,1,28,28))            
            y = nd.array(y)
            #y = nd.one_hot(y,10)            
            with autograd.record():
                y_s = net_s(g(X))                
                y_t = net_t(g(X))             
                L = l_logistic(y_s,y) + beta * l_l2loss(y_s,y_t)
                L.backward()
            trainer.step(batch_size)
            # net_t = alpha * net_t + (1-alpha) * net_s
            # alpha == 0 : copy student ;             
            net_liner(net_t,net_s,1-alpha,alpha,0)
            #metric.update(y,y_t)
            #if i % 50 == 0:
                #name, acc = metric.get()
                #print('[Epoch %d Batch %d] Training: %s=%f'%(epoch, i, name, acc))
        metric.update(y,y_t)
        name, acc = metric.get()
        print('[Epoch %d] Training: %s=%f'%(epoch, name, acc))
        name, val_acc = test()
        print('[Epoch %d] Validation: %s=%f'%(epoch, name, val_acc))        
        if epoch % 10 == 0:
            net_t.save_parameters( os.path.join('symbols','para','%s_t.params'%(modelname)) )
            net_s.save_parameters( os.path.join('symbols','para','%s_s.params'%(modelname)) )
    net_t.save_parameters( os.path.join('symbols','para','%s_t.params'%(modelname)) )
    net_s.save_parameters( os.path.join('symbols','para','%s_s.params'%(modelname)) )

if __name__ == '__main__':
    num_epochs = 10
    alpha = 0
    beta = 0
    train(20)
    for i in range(10):
        train(10,beta=0.1*i)
    for i in range(10):
        train(10,alpha=0.01*i, beta=0.1*i)
    for i in range(10):
        train(10,alpha=0.01*i, beta=1)        
    train(100,alpha=0.1,beta=1)
    train(100,alpha=0.01,beta=1,lr=0.1)
    train(100,alpha=0.01,beta=1,lr=0.01)
    