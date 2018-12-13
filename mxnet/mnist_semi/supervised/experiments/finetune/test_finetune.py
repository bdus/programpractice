#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 13 15:30:07 2018

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
from gluoncv import model_zoo as mzoo


batch_size = 1
num_test_images = 10# 
ctx = mx.cpu() #[mx.gpu(i) for i in range(num_gpus)] if num_gpus > 0 else [mx.cpu()]

# get data csv
mnistcsv = get_data.read(one_hot=True)

# get model
modelname = 'mobilenet0.25'
finetune_net = mzoo.get_model('mobilenet0.25',pretrained=True)
with finetune_net.name_scope():
    finetune_net.output = nn.Dense(10)
finetune_net.output.initialize(init.Xavier(), ctx = ctx)
finetune_net.collect_params().reset_ctx(ctx)
finetune_net.hybridize()
net = finetune_net

net.load_parameters( os.path.join('symbols','para','%s.params'%(modelname)) )


for i in range(num_test_images):
    X,_ = mnistcsv.validation.next_batch(batch_size)
    X = nd.array(X)
    X = X.reshape((-1,1,28,28))
    X = nd.concat(X,X,X,dim=1)
    y = net(X)
    ans = y.argmax(axis=1).asnumpy()        
    print("%d-th type %d" % (i, ans))   
'''
0-th type 2
1-th type 0
2-th type 9
3-th type 0
4-th type 3
5-th type 7
6-th type 0
7-th type 3
8-th type 0
9-th type 3
'''
# ===================== ====================
img_data = nd.array(mnistcsv.validation.data)
img_data = img_data.reshape((-1,1,28,28))
img_data = nd.concat(img_data,img_data,img_data,dim=1)

y = net(img_data)
Label = y.argmax(axis=1).asnumpy().astype(np.int8)
Image = np.arange(len(Label)) +1
dataframe = pd.DataFrame({'ImageId':Image,'Label':Label})
dataframe.to_csv("myout1.csv",index=False,sep=',')