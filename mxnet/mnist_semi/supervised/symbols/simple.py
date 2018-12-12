#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 12 22:14:08 2018

@author: bdus

https://mxnet.incubator.apache.org/api/python/gluon/gluon.html?highlight=hybridblock#mxnet.gluon.HybridBlock
https://github.com/dmlc/gluon-cv/blob/11eb654e938b32fd746ec5f72e09a44f35e99c7a/gluoncv/model_zoo/vgg.py

"""
__all__ = ['Simple','simple0']
import os
from mxnet.gluon import HybridBlock, nn
import mxnet as mx

class Simple(HybridBlock):
    def __init__(self, **kwargs):
        super(Simple, self).__init__(**kwargs)
        # use name_scope to give child Blocks appropriate names.
        with self.name_scope():            
            self.output = nn.HybridSequential()
            self.output.add(
                        nn.Dense(10)
                    )

    def hybrid_forward(self, F, x):
        x = self.output(x)
        return x

def simple0(**kwargs):
    return get_simple(index=0,**kwargs)

def get_simple(index,pretrained=False, ctx=mx.cpu(),
               root='/home/sans/lcx/programpractice/mxnet/mnist_semi/supervised/symbols/para', **kwargs):
    net = Simple(**kwargs)
    if pretrained:
        #https://github.com/dmlc/gluon-cv/blob/11eb654e938b32fd746ec5f72e09a44f35e99c7a/gluoncv/model_zoo/vgg.py#L116
        filepath = os.path.join(root,'simple%d.params'%(index))
        print(filepath)
        net.load_parameters(filepath)
    return net