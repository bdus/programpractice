""" Generative Adversarial Networks (GAN).

Using generative adversarial networks (GAN) to generate digit images from a
noise distribution.

References:
    - Generative adversarial nets. I Goodfellow, J Pouget-Abadie, M Mirza,
    B Xu, D Warde-Farley, S Ozair, Y. Bengio. Advances in neural information
    processing systems, 2672-2680.
    - Understanding the difficulty of training deep feedforward neural networks.
    X Glorot, Y Bengio. Aistats 9, 249-256

Links:
    - [GAN Paper](https://arxiv.org/pdf/1406.2661.pdf).
    - [MNIST Dataset](http://yann.lecun.com/exdb/mnist/).
    - [Xavier Glorot Init](www.cs.cmu.edu/~bhiksha/courses/deeplearning/Fall.../AISTATS2010_Glorot.pdf).

Author: Aymeric Damien
Project: https://github.com/aymericdamien/TensorFlow-Examples/
"""

from __future__ import division, print_function, absolute_import

import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf

# Import MNIST data
import input_data
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

# Training Params
num_steps = 100000
batch_size = 128
learning_rate = 0.0002

# Network Params
image_dim = 784 # 28*28 pixels
gen_hidden_dim = 256
disc_hidden_dim = 256
noise_dim = 100 # Noise data points

# A custom initialization (see Xavier Glorot init)
def glorot_init(shape):
    return tf.random_normal(shape=shape, stddev=1. / tf.sqrt(shape[0] / 2.))

# Store layers weight & bias


def getWeights(shape,name):
    return tf.get_variable(name=name,shape=shape,initializer=tf.contrib.layers.xavier_initializer())
    #return tf.Variable(glorot_init(shape))

def getBiases(shape,name):
    return tf.get_variable(name=name,shape=shape,initializer=tf.constant_initializer(0))
    #return tf.Variable(tf.zeros(shape))

# Generator
def generator(x):
    with tf.variable_scope('Generator') as scope:
        w1 = getWeights([noise_dim, gen_hidden_dim],'Gw1')
        b1 = getBiases([gen_hidden_dim],'Gb1')
        hidden_layer = tf.matmul(x, w1)
        hidden_layer = tf.add(hidden_layer, b1)
        hidden_layer = tf.nn.relu(hidden_layer)
        w2 = getWeights([gen_hidden_dim, image_dim],'Gw2')
        b2 = getBiases([image_dim],'Gb2')
        out_layer = tf.matmul(hidden_layer, w2)
        out_layer = tf.add(out_layer, b2)
        out_layer = tf.nn.sigmoid(out_layer)
        return out_layer


# Discriminator
def discriminator(x ,reuse=False):
    with tf.variable_scope('Discriminator') as scope:
        if reuse:
            scope.reuse_variables()
        w1 = getWeights([image_dim, disc_hidden_dim],'Dw1')
        b1 = getBiases([disc_hidden_dim],'Db1')
        w2 = getWeights([disc_hidden_dim, 1],'Dw2')
        b2 = getBiases([1],'Db2')
        hidden_layer = tf.matmul(x, w1)
        hidden_layer = tf.add(hidden_layer, b1)
        hidden_layer = tf.nn.relu(hidden_layer)
        out_layer = tf.matmul(hidden_layer, w2)
        out_layer = tf.add(out_layer, b2)
        out_layer = tf.nn.sigmoid(out_layer)
    return out_layer

# Build Networks
# Network Inputs
gen_input = tf.placeholder(tf.float32, shape=[None, noise_dim], name='input_noise')
disc_input = tf.placeholder(tf.float32, shape=[None, image_dim], name='disc_input')

# Build Generator Network
gen_sample = generator(gen_input)

# Build 2 Discriminator Networks (one from noise input, one from generated samples)
disc_real = discriminator(disc_input)
disc_fake = discriminator(gen_sample,reuse=True)

# Build Loss
gen_loss = -tf.reduce_mean(tf.log(disc_fake))
disc_loss = -tf.reduce_mean(tf.log(disc_real) + tf.log(1. - disc_fake))

# Build Optimizers
optimizer_gen = tf.train.AdamOptimizer(learning_rate=learning_rate)
optimizer_disc = tf.train.AdamOptimizer(learning_rate=learning_rate)

# Training Variables for each optimizer
# By default in TensorFlow, all variables are updated by each optimizer, so we
# need to precise for each one of them the specific variables to update.
# Generator Network Variables
gen_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES,scope='Generator')
# Discriminator Network Variables
disc_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES,scope='Discriminator')

# Create training operations
train_gen = optimizer_gen.minimize(gen_loss, var_list=gen_vars)
train_disc = optimizer_disc.minimize(disc_loss, var_list=disc_vars)
# train_gen = optimizer_gen.minimize(gen_loss)
# train_disc = optimizer_disc.minimize(disc_loss)

# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()

epoch_list = []
gloss_list = []
dloss_list = []


# Start training
sess = tf.Session()

# Run the initializer
sess.run(init)

for i in range(1, num_steps+1):
    # Prepare Data
    # Get the next batch of MNIST data (only images are needed, not labels)
    batch_x, _ = mnist.train.next_batch(batch_size)
    # Generate noise to feed to the generator
    z = np.random.uniform(-1., 1., size=[batch_size, noise_dim])

    # Train
    feed_dict = {disc_input: batch_x, gen_input: z}
    _, _, gl, dl = sess.run([train_gen, train_disc, gen_loss, disc_loss],
                            feed_dict=feed_dict)
    if i % 1000 == 0 or i == 1:
        epoch_list.append(i)
        gloss_list.append(gl)
        dloss_list.append(dl)
        print('Step %i: Generator Loss: %f, Discriminator Loss: %f' % (i, gl, dl))

f1 = plt.figure(1)
# plt.plot(epoch_list,gloss_list/np.max(gloss_list),'r-',label='G_loss')
# plt.plot(epoch_list,dloss_list/np.max(dloss_list),'r-',label='D_loss')
plt.plot(epoch_list,gloss_list,'r-',label='G_loss')
plt.plot(epoch_list,dloss_list,'b-',label='D_loss')
plt.legend()
f2 = plt.figure(2)
# plt.plot(epoch_list,gloss_list/np.max(gloss_list),'r-',label='G_loss')
# plt.plot(epoch_list,dloss_list/np.max(dloss_list),'r-',label='D_loss')
plt.plot(epoch_list,gloss_list/np.max(gloss_list),'r-',label='G_loss')
plt.plot(epoch_list,dloss_list/np.max(dloss_list),'b-',label='D_loss')
plt.legend()

# Generate images from noise, using the generator network.
f, a = plt.subplots(4, 10, figsize=(10, 4))
for i in range(10):
    # Noise input.
    z = np.random.uniform(-1., 1., size=[4, noise_dim])
    g = sess.run([gen_sample], feed_dict={gen_input: z})
    g = np.reshape(g, newshape=(4, 28, 28, 1))
    # Reverse colours for better display
    g = -1 * (g - 1)
    for j in range(4):
        # Generate image from noise. Extend to 3 channels for matplot figure.
        img = np.reshape(np.repeat(g[j][:, :, np.newaxis], 3, axis=2),
                            newshape=(28, 28, 3))
        a[j][i].imshow(img)

plt.show()
