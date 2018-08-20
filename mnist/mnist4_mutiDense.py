#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Aug 11 21:42:01 2018

@author: bdus
@time Aug 11
@ minist Dense

@env py3.x
"""
import tensorflow as tf
import input_data
import matplotlib.pyplot as plt
<<<<<<< HEAD
=======
import numpy as np
>>>>>>> dev

## dataset

mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

## model
def weight_variable(shape):
    tmpVar = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(tmpVar)


def bias_variable(shape):
    tmpVar = tf.constant(0.1,shape=shape)
    return tf.Variable(tmpVar)


x = tf.placeholder("float",[None,784])
y = tf.placeholder("float",[None,10])


W1 = weight_variable([784,256])
b1 = bias_variable([256])
h1 = tf.nn.softmax((tf.matmul(x,W1) + b1))

W2 = weight_variable([256,10])
b2 = bias_variable([10])

y_hat = tf.nn.softmax((tf.matmul(h1,W2) + b2))

## loss

cross_entropy = -tf.reduce_sum(y*tf.log(y_hat))

## train

optimizer = tf.train.GradientDescentOptimizer(0.01)
train = optimizer.minimize(cross_entropy)

## acc

correct_prediction = tf.equal(tf.argmax(y,1),tf.argmax(y_hat,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))

## run

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
epoch_list = []
loss_list = []
acc_list = []

for i in range(20000):
    batch_x, batch_y = mnist.train.next_batch(100)
    sess.run(train, feed_dict={x:batch_x, y:batch_y})
    if i%200 == 0:
        myloss,myacc = sess.run([cross_entropy,accuracy],feed_dict={x:mnist.validation.images,y:mnist.validation.labels})
        epoch_list.append(i)
        loss_list.append(myloss)
        acc_list.append(myacc)
        print("step %d ,acc %g"%(i,myacc))


<<<<<<< HEAD
# fig = plt.gcf()
# plt.plot(epoch_list,loss_list,label='loss')
# plt.show
=======
plt.figure(1)
plt.plot(epoch_list,loss_list/np.max(loss_list),'r-',label='loss')

plt.plot(epoch_list,acc_list,'b-',label='acc')
plt.legend()
plt.show()
>>>>>>> dev
