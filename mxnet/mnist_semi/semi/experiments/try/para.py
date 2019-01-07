p#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 13 20:38:01 2018

@author: bdus

parameter
"""
import mxnet as mx
from mxnet import init, nd
from mxnet.gluon import nn

# define networks
## net
net = nn.Sequential()
with net.name_scope():
    net.add(nn.Dense(256,activation='relu'))
    net.add(nn.Dense(10))
net.initialize()

x = nd.random.uniform(shape=(2,20))
y = net(x)
net[0].weight.data()[0]

## net2
net2 = nn.Sequential()
with net2.name_scope():
    net2.add(nn.Dense(256,activation='relu'))
    net2.add(nn.Dense(10))
net2.initialize(init=init.Constant(1),force_reinit=True)
#x = nd.random.uniform(shape=(2,20))
y = net2(x)
net2[0].weight.data()[0]


# show all parameters
for k, v in net.collect_params().items():
    print(k, v.data().size)

for k, v in net2.collect_params().items():
    print(k, v.data().size)


# para

para = net.collect_params()  
para2 = net2.collect_params()

x = para['sequential0_dense0_weight'].data()[0]
print (x.shape,x)

x2 = para2['sequential1_dense0_weight'].data()[0]
x2.shape
x2

para['sequential0_dense0_weight'].set_data(para2['sequential1_dense0_weight'].data(mx.cpu()))

x = para['sequential0_dense0_weight'].data()[0]
print (x.shape,x)

# copy
para = net.collect_params()  
para2 = net2.collect_params()

print('before copy',para['sequential0_dense1_weight'].data()[0][0])

for (k, v) , (k2, v2) in zip( net.collect_params().items() , net2.collect_params().items() ):
    #print(k, v.data().size)
    #print(k2, v2.data().size)
    v.set_data(v2.data())
    
   
para = net.collect_params()
print('after copy',para['sequential0_dense1_weight'].data()[0][0])

for (k, v) , (k2, v2) in zip( net.collect_params().items() , net2.collect_params().items() ):
    v.data() ==v2.data()
    
#para functions
for (k, v) , (k2, v2) in zip( net.collect_params().items() , net2.collect_params().items() ):
    #print(k, v.data().size)
    #print(k2, v2.data().size)
    v.set_data(v2.data() + 10 )

print('after copy',para['sequential0_dense1_weight'].data()[0][0])
for (k, v) , (k2, v2) in zip( net.collect_params().items() , net2.collect_params().items() ):
    #print(k, v.data().size)
    #print(k2, v2.data().size)
    v.set_data(v2.data() * 0.1 )

print('after copy',para['sequential0_dense1_weight'].data()[0][0])

for (k, v) , (k2, v2) in zip( net.collect_params().items() , net2.collect_params().items() ):
    #print(k, v.data().size)
    #print(k2, v2.data().size)
    v.set_data(v2.data() * 1 + v.data() * 10)

print('after copy',para['sequential0_dense1_weight'].data()[0][0])

#https://mxnet.incubator.apache.org/tutorials/gluon/customop.html?highlight=operator

def net_liner(net,net2,x1,x2,b):
    for (k, v) , (k2, v2) in zip( net.collect_params().items() , net2.collect_params().items() ):
        v.set_data(v2.data() * x1 + v.data() * x2 + b)

def get_para(net):
    """
    net = nn.Sequential()
    with net.name_scope():
        net.add(nn.Dense(256,activation='relu'))
        net.add(nn.Dense(10))
    net.initialize()
    
    x = nd.random.uniform(shape=(2,20))
    y = net(x)
    net[0].weight.data()[0]    
    #
    para = get_para(net)
    para['sequential0_dense0_weight'][0]
    """
    para = {}
    for k, v in net.collect_params().items():
        para[k]= v.data()
        print(k, v.data().size)
    return para

def set_net(net,para):
    """
    net = nn.Sequential()
    with net.name_scope():
        net.add(nn.Dense(256,activation='relu'))
        net.add(nn.Dense(10))
    net.initialize()
    
    x = nd.random.uniform(shape=(2,20))
    y = net(x)
    net[0].weight.data()[0]
    
    ## net2
    net2 = nn.Sequential()
    with net2.name_scope():
        net2.add(nn.Dense(256,activation='relu'))
        net2.add(nn.Dense(10))
    net2.initialize(init=init.Constant(1),force_reinit=True)
    #x = nd.random.uniform(shape=(2,20))
    y = net2(x)
    net2[0].weight.data()[0]
    
    para2 = get_para(net2)
    set_net(net,para2)
    net[0].weight.data()[0]
        
    """
    for (k, v),(k2,v2) in zip( net.collect_params().items() , para.items() ):
        v.set_data(v2)
        print(k, v.data().size)

def show_dict(para):
    for k,v in para.items():
        print(k, v.shape)
   
