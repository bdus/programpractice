#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Aug  9 20:54:29 2018

@author: sans
@time Aug 9
@env py3.x

@datebase
    MNIST 
@Model
    Muti-layer CNN

"""
import numpy as np
import tensorflow as tf
import input_data

## dataset



mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

## model
def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)
  
def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

x = tf.placeholder("float", [None, 784])

x_image = tf.reshape(x, [-1,28,28,1])

# first layer
W_conv1 = weight_variable([5, 5, 1, 32]) 
b_conv1 = bias_variable([32])

h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)

# second layer
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)

#decent
W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])

h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)

#drop out
keep_prob = tf.placeholder("float")
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

# full conn
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])

y_conv=tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

## loss
y_ = tf.placeholder("float", [None,10])
cross_entropy = -tf.reduce_sum(y_*tf.log(y_conv))

## train
optimizer = tf.train.AdamOptimizer(1e-4)
train = optimizer.minimize(cross_entropy)


## acc

correct_prediction = tf.equal(tf.argmax(y_conv,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

sess = tf.Session()
sess.run(tf.global_variables_initializer())

for i in range(20000):
    batch = mnist.train.next_batch(50)
    sess.run(train,feed_dict={
        x:batch[0], y_:batch[1], keep_prob: 0.5})
    if i%100 ==0:
        print("step %d , acc %g"%(i,sess.run(accuracy,feed_dict={x:batch[0], y_:batch[1], keep_prob: 1.0})))
               
print("test acc %g" % sess.run(accuracy,feed_dict={x: mnist.test.images, y_: mnist.test.labels, keep_prob:1.0}))
