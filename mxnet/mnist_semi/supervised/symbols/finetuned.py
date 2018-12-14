#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 13 16:13:27 2018

@author: bdus

"""


__all__ = ['Finetuned','ft_mobilenet0_25']
import os
from mxnet.gluon import HybridBlock, nn
import mxnet as mx
import mxnet.ndarray as nd
from gluoncv import model_zoo as mzoo

modelnamelist = {
        0:'mobilenet0.25'
        }

class Finetuned(HybridBlock):
    def __init__(self,index=0,**kwargs):
        super(Finetuned, self).__init__(**kwargs)
        # use name_scope to give child Blocks appropriate names.
        self.index = index
        self.model_name = modelnamelist[index]
        self.ctx = mx.cpu()
        if index == 0:
            finetune_net = mzoo.get_model(modelnamelist[index],pretrained=True)
            with finetune_net.name_scope():
                finetune_net.output = nn.Dense(10) 
            finetune_net.output.initialize(mx.init.Xavier(), ctx = self.ctx)
            finetune_net.collect_params().reset_ctx(self.ctx)
            finetune_net.hybridize()
            self.output = finetune_net
                
        else:
            pass
            
    def hybrid_forward(self, F, x):        
        x = self.output(x)
        return x
    
    def __getitem__(self, key):
        return self.output[key]
    
    def __len__(self):
        return len(self.output)

    
def ft_mobilenet0_25(**kwargs):
    return get_finetune(index=0,**kwargs)   

def get_finetune(index,pretrained=False, ctx=mx.cpu(),
               root='/home/sans/lcx/programpractice/mxnet/mnist_semi/supervised/symbols/para', **kwargs):
    net = Finetuned(index,**kwargs)
    if pretrained:
        #https://github.com/dmlc/gluon-cv/blob/11eb654e938b32fd746ec5f72e09a44f35e99c7a/gluoncv/model_zoo/vgg.py#L116
        filepath = os.path.join(root,'%s.params'%(net.model_name))
        #print(filepath)
        net.load_parameters(filepath)        
        net.collect_params().reset_ctx(ctx)
        net.hybridize()
    return net
