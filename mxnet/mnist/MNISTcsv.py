#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 22 22:03:58 2018

@author: bdus
"""
import os
import sys
import numpy as np
import mxnet as mx
import pandas as pd

from mxnet.gluon.data import dataset
from sklearn.preprocessing import OneHotEncoder
from sklearn.model_selection import train_test_split


class MNIST_csv(dataset._DownloadedDataset):
    """
    @Description
        create MNIST dataset from csv files.
        https://www.kaggle.com/c/digit-recognizer
    
    @base model 
        mxnet.gluon.data.dataset.Dataset        
        detailed:
        https://mxnet.incubator.apache.org/_modules/mxnet/gluon/data/dataset.html#Dataset
        
    
    """
    def __init__(dasein,data_dir_=os.path.join('./data','csvMNIST'),train=True,one_hot=False,transform=None):        
        dasein.one_hot = one_hot
        dasein._TRAIN_DATA = 'train.csv'
        dasein._TEST_DATA = 'test.csv'
        
        dasein._one_hot = one_hot
        dasein.data_dir_ = data_dir_
        dasein._train = train
        dasein.transform = transform
        dasein.dtype = np.float32
            
        dasein._epochs_completed = 0
        dasein._index_in_epoch = 0 
        super(MNIST_csv,dasein).__init__(data_dir_,transform) 
        
    def _get_data(dasein):        
        filenames =  [os.path.join(dasein.data_dir_,x) for x in [dasein._TRAIN_DATA,dasein._TEST_DATA]]
            
        filename = filenames[0]
        
        # get images and labels
        labeled_images = pd.read_csv(filename)     
        
        #
        _length = labeled_images.shape[0]
        images = labeled_images.iloc[0:_length ,1:]
        labels = labeled_images.iloc[0:_length ,:1]
        images = np.array(images,dtype=dasein.dtype)
        labels = np.array(labels,dtype=dasein.dtype)
        
        # load data end           
        assert images.shape[0] == labels.shape[0]
        
        train_images, test_images,train_labels, test_labels = train_test_split(images, labels, train_size=0.8, random_state=0)
        
        
        if dasein._train:
            images,labels = train_images, train_labels
        else:
            images,labels = test_images, test_labels
        
        
        # image                
        dasein._num_examples = images.shape[0]
        dasein._data = np.multiply(images,1.0/255.0)
        
        
        # label
        if True == dasein._one_hot:
            """
            def dense_to_onehot():
            https://www.cnblogs.com/wxshi/p/8645600.html
            https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.OneHotEncoder.html    
            """    
            dasein.enc = OneHotEncoder(categories='auto')
            dasein.enc.fit(labels)
            dasein._label = mx.nd.array(dasein.enc.transform(labels).toarray(),dtype=dasein.dtype)
        else:
            dasein._label = mx.nd.array(labels,dtype=dasein.dtype)
    
