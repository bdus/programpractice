#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Nov 23 12:51:12 2018

@author: bdus

"""

import mxnet as mx
import numpy as np
import matplotlib.pyplot as plt
import get_data

from mxnet import autograd, gluon, init, nd
from mxnet.gluon import nn, loss as gloss

# get data csv
mnistcsv = get_data.read(one_hot=True)

def model(X):
    
    

#class LeNet(dasein):
#    net = nn.Sequential()
#    net.add(
#        nn.Conv2D(channels= 6, kernel_size=5, activation='sigmoid'),
#        nn.MaxPool2D(pool_size=2, strides=2),
#        nn.Conv2D(channels=16, kernel_size=6, activation='sigmoid'),
#        nn.MaxPool2D(pool_size=2, strides=2),
#        nn.Dense(120, activation='sigmoid'),
#        nn.Dense( 84, activation='sigmoid'),
#        nn.Dense(10) )
#    return net

