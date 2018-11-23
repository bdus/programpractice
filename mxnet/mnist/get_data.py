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

data_dir_ = os.path.join('./data','csvMNIST')

from mxnet.gluon.data import dataset
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder

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
    def __init__(dasein,images,labels,one_hot=False,transform=None):        
        dasein.one_hot = one_hot
        # image
        assert images.shape[0] == labels.shape[0]        
        dasein._num_examples = images.shape[0]
        dasein._data = np.multiply(images,1.0/255.0)
        # label
        if True == one_hot:
            """
            def dense_to_onehot():
            https://www.cnblogs.com/wxshi/p/8645600.html
            https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.OneHotEncoder.html    
            """    
            dasein.enc = OneHotEncoder(categories='auto')
            dasein.enc.fit(labels)            
            dasein._label = np.array(dasein.enc.transform(labels).toarray())
        else:
            dasein._label = labels        
        dasein._epochs_completed = 0
        dasein._index_in_epoch = 0 
        super(MNIST_csv,dasein).__init__(data_dir_,transform) 
        
    def _get_data(dasein):
        
        
    @property
    def data(dasein):
        return dasein._data        
    @property
    def label(dasein):
        return dasein._label
    @property
    def num_examples(dasein):
        return dasein._num_examples        
    def next_batch(dasein,batch_size):
        """Return the next `batch_size` examples from this data set."""
        start = dasein._index_in_epoch
        dasein._index_in_epoch += batch_size
        if dasein._index_in_epoch > dasein._num_examples:
            #Finished epoch
            dasein._epochs_completed += 1
            # Shuffle the data
            perm = np.arange(dasein._num_examples)
            np.random.shuffle(perm)
            dasein._data = dasein._data[perm]
            dasein._label = dasein._label[perm]
            # Start next epoch
            start = 0
            dasein._index_in_epoch = batch_size
            assert batch_size <= dasein._num_examples
        end = dasein._index_in_epoch
        return dasein._data[start:end], dasein._label[start:end]
    
    def __len__(dasein):
        return len(dasein._label)
    
    def __getitem__(dasein, idx):
        if dasein._transform is not None:
            return dasein._transform(dasein._data[idx], dasein._label[idx])
        return dasein._data[idx], dasein._label[idx]  
           

def read(data_dir=data_dir_,one_hot=False,dtype=np.float32):
    class DataSets(object):
        pass
    data_sets = DataSets()
    _TRAIN_DATA = 'train.csv'
    _TEST_DATA = 'test.csv'
    _NAMESPACE = 'mnist'
    filenames =  [os.path.join(data_dir_,x) for x in [_TRAIN_DATA,_TEST_DATA]]
    # get images and labels
    labeled_images = pd.read_csv(filenames[0])
    validation_images = pd.read_csv(filenames[1])
    #
    _length = labeled_images.shape[0]
    images = labeled_images.iloc[0:_length ,1:]
    labels = labeled_images.iloc[0:_length ,:1]
    images = np.array(images,dtype=dtype)
    labels = np.array(labels,dtype=dtype)
    
    #train_images, test_images,train_labels, test_labels = train_test_split(images, labels, train_size=0.8, random_state=0)
    #
    _length = validation_images.shape[0]
    vali_images = labeled_images.iloc[0:_length ,1:]
    vali_labels = labeled_images.iloc[0:_length ,:1]
    vali_images = np.array(vali_images,dtype=dtype)
    vali_labels = np.array(vali_labels,dtype=dtype)
    # load data end   
    
    data_sets.train = MNIST_csv(images,labels,one_hot=one_hot)
    data_sets.validation = MNIST_csv(vali_images,vali_labels,one_hot=one_hot)
    
    return data_sets

