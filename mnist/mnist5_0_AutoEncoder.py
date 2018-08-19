#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Created on Thu Aug 18 14:26 2018

@author: bdus
@ Auto Encoder Dense

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
    tmpVar = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(tmpVar)


def bias_variable(shape):
    tmpVar = tf.constant(0.1,shape=shape)
    return tf.Variable(tmpVar)

def encoder(x):
    #Dense hidden layer 1
    W1 = weight_variable([784,256])
    b1 = bias_variable([256])
    h1 = tf.nn.sigmoid(tf.add(tf.matmul(x,W1),b1))
    #2
    W2 = weight_variable([256,128])
    b2 = bias_variable([128])
    return tf.nn.sigmoid(tf.add(tf.matmul(h1,W2),b2))

def decoder(x):
    #Dense hidden layer 1
    W1 = weight_variable([128,256])
    b1 = bias_variable([256])
    h1 = tf.nn.sigmoid(tf.add(tf.matmul(x,W1),b1))
    #2
    W2 = weight_variable([256,784])
    b2 = bias_variable([784])
    return tf.nn.sigmoid(tf.add(tf.matmul(h1,W2),b2))

x = tf.placeholder("float",[None,784])
#y = tf.placeholder("float",[None,128])
#x_hat = tf.placeholder("float",[None,784])

y = encoder(x)
x_hat = decoder(y)

#loss

loss = tf.reduce_mean( tf.pow(x-x_hat,2) )

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



plt.figure(1)
plt.plot(epoch_list,loss_list/np.max(loss_list),'r-',label='loss')
plt.legend()


f, a = plt.subplots(2,10,figsize=(10,2))
for i in range(10):
    a[0][i].imshow(np.reshape(mnist.test.images[i], (28, 28)))
    a[1][i].imshow(np.reshape(encode_decode[i], (28, 28)))

plt.show()
plt.waitforbuttonpress()

