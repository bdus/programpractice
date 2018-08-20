#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Created on Thu Aug 18 14:26 2018

@author: bdus
@ Auto Encoder convolution

@env py3.x
"""


import tensorflow as tf
import input_data
import matplotlib.pyplot as plt
import numpy as np

#para

learning_rate = 0.01
training_epochs = 10
batch_size = 256

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


def deconv2d(x, W, output_shape):
  return tf.nn.conv2d_transpose(x, W, output_shape, strides = [1, 1, 1, 1], padding = 'SAME')
    

    
def encoder(x): #x 28x28x1
    # first layer
    W_conv1 = weight_variable([3, 3, 1, 32])  # 28x28x32
    b_conv1 = bias_variable([32])
    
    h_conv1 = tf.nn.relu(conv2d(x, W_conv1) + b_conv1)
    h_pool1 = max_pool_2x2(h_conv1) # 14x14x32

    # second layer
    W_conv2 = weight_variable([3, 3, 32, 32]) #14x14x32
    b_conv2 = bias_variable([32])

    h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
    h_pool2 = max_pool_2x2(h_conv2) # 7x7x32

    # third layer
    W_conv3 = weight_variable([3,3,32,16]) #7x7x16
    b_conv3 = bias_variable([16])

    h_conv3 = tf.nn.relu(conv2d(h_pool2, W_conv3) + b_conv3)
    return max_pool_2x2(h_conv3) #4x4x16

def decoder(x):
    # first layer
    # W_deconv1 = weight_variable([3,3,16,32]) #4x4x32
    # h_deconv1 = deconv2d(x,W_deconv1,[batch_size,7,7,32])  #7x7x32

    # #second layer
    # W_deconv2 = weight_variable([3,3,32,32])
    # h_deconv2 = deconv2d(h_deconv1,W_deconv2,[batch_size,14,14,32])

    # #third layer
    # W_deconv3 = weight_variable([3,3,32,32])
    # h_deconv3 = deconv2d(h_deconv2,W_deconv3,[batch_size,28,28,32])

    # #output conv layer
    # W_conv_out = weight_variable([3,3,32,1])
    # b_conv_out = bias_variable([1])
    # return tf.nn.relu(conv2d(h_deconv3,W_conv_out)+b_conv_out)




x = tf.placeholder("float",[None,784])
x_image = tf.reshape(x, [-1,28,28,1])

#y = tf.placeholder("float",[None,128])
#x_hat = tf.placeholder("float",[None,784])

y = encoder(x_image)
x_hat = decoder(y)

x_output = tf.reshape(x_hat,shape=[-1,784])

#loss

loss = tf.reduce_mean( tf.pow(x-x_output,2) )

#train

optimizer = tf.train.AdamOptimizer(learning_rate)
train = optimizer.minimize(loss)

## run

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)

epoch_list = []
loss_list = []
acc_list = []

total_batch = int(mnist.train.num_examples/batch_size)
for epoch in range(training_epochs):
    for i in range(total_batch):
        batch_xs, batch_ys = mnist.train.next_batch(batch_size)
        sess.run(train,feed_dict={x:batch_xs})
        if i%200 == 0:
            tmpi = epoch*total_batch+i
            myloss = sess.run(loss,feed_dict={x:batch_xs})
            epoch_list.append(tmpi)
            loss_list.append(myloss)
            print("step %d ,loss %g"%(tmpi,myloss))

encode_decode = sess.run(x_hat,feed_dict={x:mnist.test.images[:10]})
f, a = plt.subplots(2,10,figsize=(10,2))
for i in range(10):
    a[0][i].imshow(np.reshape(mnist.test.images[i], (28, 28)))
    a[1][i].imshow(np.reshape(encode_decode[i], (28, 28)))
plt.show()

