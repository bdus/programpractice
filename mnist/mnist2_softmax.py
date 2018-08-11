#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Aug  9 18:28:04 2018

@author: bdus
@time Aug 9
@ minist begin

@env py3.x


"""

import input_data
import tensorflow as tf
import numpy as np

# dataset

mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)


# model
x = tf.placeholder("float", [None, 784])

W = tf.Variable(tf.zeros([784,10])) 
b = tf.Variable(tf.zeros([10]))

y = tf.nn.softmax(tf.matmul(x,W) + b)


# loss

y_ = tf.placeholder("float", [None,10])
cross_entropy = -tf.reduce_sum(y_*tf.log(y))


# training 
optimizer = tf.train.GradientDescentOptimizer(0.01)
train = optimizer.minimize(cross_entropy)

# run

init = tf.global_variables_initializer()

sess = tf.Session()
sess.run(init)

for i in range(1000):
    batch_xs, batch_ys = mnist.train.next_batch(100)
    sess.run(train, feed_dict={x: batch_xs, y_: batch_ys})
   
    
# acc
    
correct_prediction = tf.equal(tf.argmax(y,1), tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
print(sess.run(accuracy, feed_dict={x: mnist.test.images, y_: mnist.test.labels}))
