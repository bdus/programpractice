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

class MNIST_csv(dataset.Dataset):
    """
    @Description
        create MNIST dataset from csv files.
        https://www.kaggle.com/c/digit-recognizer
    
    @base model 
        mxnet.gluon.data.dataset.Dataset
        detailed:
        https://mxnet.incubator.apache.org/_modules/mxnet/gluon/data/dataset.html#Dataset
    
    """
    def __init__(dasein,images,labels,one_hot=False):
        super(MNIST_csv,dasein).__init__()
        pass
        
                
        
def dense_to_onehot():
    pass
        
def _get_data(data_dir,one_hot=False,dtype=float):
    class DataSets(dataset.Dataset):
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
    train_images, test_images,train_labels, test_labels = train_test_split(images, labels, train_size=0.8, random_state=0)
    #
    _length = validation_images.shape[0]
    vali_images = labeled_images.iloc[0:_length ,1:]
    vali_labels = labeled_images.iloc[0:_length ,:1]
    
    data_sets.train = MNIST_csv()

    
        