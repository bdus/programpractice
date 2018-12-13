#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 12 21:38:52 2018

@author: bdus

baseline
https://github.com/bdus/programpractice/blob/master/mxnet/mnist_baseline/test_model.py
"""


import _init_paths

import os
import mxnet as mx
import numpy as np

from dataset import get_data
from symbols import symbols
import pandas as pd


batch_size = 1
num_test_images = 10# 

# get data csv
mnistcsv = get_data.read(one_hot=True)


# get model

net = symbols.get_model('simple2',pretrained=True)

#net.load_parameters( os.path.join('symbols','para','simple0.params') )

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
dataframe.to_csv("myout0.csv",index=False,sep=',')