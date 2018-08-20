#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Aug 19 12:41:30 2018

@author: sans
"""

import input_data
import tensorflow as tf
import numpy as np
import matplotlib.pylab as plt

#dataset
mnist = input_data.read_data_sets("MNIST_data", one_hot=True)

# Training Params
num_steps = 100000
batch_size = 128
learning_rate = 0.0002

# Network Params
image_dim = 784 # 28*28 pixels
gen_hidden_dim = 256
disc_hidden_dim = 256
noise_dim = 100 # Noise data points

## model
# A custom initialization (see Xavier Glorot init)
def glorot_init(shape):
    return tf.random_normal(shape=shape, stddev=1. / tf.sqrt(shape[0] / 2.))

def weight_variable(shape):
    return tf.Variable(glorot_init(shape))
    # tmpVar = tf.truncated_normal(shape, stddev=0.1)
    # return tf.Variable(tmpVar)

def bias_variable(shape):
    return tf.Variable(tf.zeros(shape))
    # tmpVar = tf.constant(0.1,shape=shape)
    # return tf.Variable(tmpVar)

def generator(z,reuse=False):
    with tf.variable_scope("Generator",reuse=reuse):
        #input noize 100x1 -> 256x1
        W1 = weight_variable([noise_dim,gen_hidden_dim])
        b1 = bias_variable([gen_hidden_dim])
        h1 = tf.nn.sigmoid( tf.add(tf.matmul(z,W1),b1) )
        #output
        W2 = weight_variable([gen_hidden_dim,image_dim])
        b2 = bias_variable([image_dim])
        return tf.nn.sigmoid( tf.add(tf.matmul(h1,W2),b2) )


def discriminator(x,reuse=False):
    with tf.variable_scope("Discriminator",reuse=reuse):
        #input 
        W1 = weight_variable([image_dim,disc_hidden_dim])
        b1 = bias_variable([disc_hidden_dim])
        h1 = tf.nn.sigmoid( tf.add(tf.matmul(x,W1),b1) )
        #output
        W2 = weight_variable([disc_hidden_dim,1])
        b2 = tf.Variable(tf.zeros([1]))
        return tf.nn.sigmoid( tf.add(tf.matmul(h1,W2),b2) )

x_input = tf.placeholder(tf.float32,[None,image_dim])
z_noise = tf.placeholder(tf.float32,[None,noise_dim])

G_sample = generator(z_noise,True)

D_real = discriminator(x_input,True)
D_fake = discriminator(G_sample,True)

# loss

G_loss = -tf.reduce_mean(tf.log(D_fake))
D_loss = -tf.reduce_mean(tf.log(D_real) + tf.log(1. - D_fake))

# train
optimizer_g = tf.train.AdamOptimizer(learning_rate)
optimizer_d = tf.train.AdamOptimizer(learning_rate)

# Generator Network Variables
gen_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope='Generator')
# Discriminator Network Variables
disc_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope='Discriminator')

train_gen = optimizer_g.minimize(G_loss,var_list=gen_vars)
train_disc = optimizer_d.minimize(D_loss,var_list=disc_vars)

init = tf.global_variables_initializer()
sess = tf.Session()

sess.run(init)


for i in range(1, 2000+1):
    # Prepare Data
    # Get the next batch of MNIST data (only images are needed, not labels)
    batch_x, _ = mnist.train.next_batch(batch_size)
    # Generate noise to feed to the generator
    z = np.random.uniform(-1., 1., size=[batch_size, noise_dim])

    # Train
    
    sess.run([train_gen, train_disc], feed_dict={x_input:batch_x,z_noise:z})
    if i % 1000 == 0 or i == 1:
        gl, dl = sess.run([G_loss, D_loss], feed_dict={x_input:batch_x,z_noise:z})
        
        print('Step %i: Generator Loss: %f, Discriminator Loss: %f' % (i, gl, dl))


    
f, a = plt.subplots(4, 10, figsize=(10, 4))
for i in range(10):
    # Noise input.
    z = np.random.uniform(-1., 1., size=[4, noise_dim])
    g = sess.run([G_sample], feed_dict={z_noise:z})
    g = np.reshape(g, newshape=(4, 28, 28, 1))
    # Reverse colours for better display
    g = -1 * (g - 1)
    for j in range(4):
        # Generate image from noise. Extend to 3 channels for matplot figure.
        img = np.reshape(np.repeat(g[j][:, :, np.newaxis], 3, axis=2),
                         newshape=(28, 28, 3))
        a[j][i].imshow(img)

f.show()
plt.draw()
plt.waitforbuttonpress()
    


