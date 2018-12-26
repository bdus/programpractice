#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 26 11:57:25 2018

@author: bdus

We have prepared the voc dataset according to [link](https://gluon-cv.mxnet.io/build/examples_datasets/pascal_voc.html#sphx-glr-build-examples-datasets-pascal-voc-py)

this script will demonstrate loding images and labels from voc dataset with 'gluon'

"""

from gluoncv import data, utils
from matplotlib import pyplot as plt

# load all dataset from voc dataset
train_dataset = data.VOCDetection(splits=[(2007, 'trainval'), (2012, 'trainval')])
val_dataset = data.VOCDetection(splits=[(2007, 'test')])
print('Num of training images:', len(train_dataset))
print('Num of validation images:', len(val_dataset))

# now we will visualize one example
 
train_image, train_label = train_dataset[5]
print('Image size (height, width, RGB):', train_image.shape)
# Take bounding boxes by slice columns from 0 to 4
bounding_boxes = train_label[:, :4]
print('Num of objects:', bounding_boxes.shape[0])
print('Bounding boxes (num_boxes, x_min, y_min, x_max, y_max):\n',
      bounding_boxes)
# take class ids by slice the 5th column
class_ids = train_label[:, 4:5]
print('Class IDs (num_boxes, ):\n', class_ids)
utils.viz.plot_bbox(train_image.asnumpy(), bounding_boxes, scores=None,
                    labels=class_ids, class_names=train_dataset.classes)
plt.show()