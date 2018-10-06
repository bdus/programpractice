#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
model file
"""
import tensorflow as tf
import input_data
import matplotlib.pyplot as plt
import numpy as np
import os 


# def getWeights(shape,name):
#     return tf.get_variable(name=name,shape=shape,initializer=tf.contrib.layers.xavier_initializer())
#     #return tf.Variable(glorot_init(shape))

# def getBiases(shape,name):
#     return tf.get_variable(name=name,shape=shape,initializer=tf.constant_initializer(0))
#     #return tf.Variable(tf.zeros(shape))

def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

class mutiDense():
    def __init__(self):
        self.name = 'mutiDense'

    def __call__(self,x): # x : [None,784]
        with tf.variable_scope(self.name) as scope:
            shared = tf.layers.dense(x,256)
            shared = tf.layers.dense(shared,10)
            return tf.nn.softmax(shared)

    @property
    def vars(self):
        return tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES,scope=self.name)

class mutiCNN():
    def __init__(self):
        self.name = 'mutiCNN'
        self.isTrain = True

    def __call__(self,x): # x : [None,784]
        with tf.variable_scope(self.name) as scope:
            x_image = tf.reshape(x, [-1,28,28,1])
            shared = tf.layers.conv2d(
                inputs=x_image,filters=32,kernel_size=[5, 5],padding="same",
                activation=tf.nn.relu)
            shared = tf.layers.max_pooling2d(inputs=shared, pool_size=[2, 2], strides=2)
            
            shared = tf.layers.conv2d(
                inputs=shared,filters=64,kernel_size=[5, 5],
                padding="same",activation=tf.nn.relu)
                
            shared = tf.layers.max_pooling2d(inputs=shared, pool_size=[2, 2], strides=2)
            
           #reshape full-conn
            shared = tf.reshape(shared, [-1, 7*7*64])
            shared = tf.layers.dense(shared,1024,activation=tf.nn.relu)
            
            #drop out
            if self.isTrain == True:
                keep_prob = tf.constant(0.5,'float')
            else: 
                keep_prob = tf.constant(1,'float')
            
            shared = tf.nn.dropout(shared, keep_prob)
            #full-conn, output
            shared = tf.layers.dense(shared,10)
            return tf.nn.softmax(shared)

    @property
    def vars(self):
        return tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES,scope=self.name)           


class myClassifyer():
    def __init__(self,model):
        #paras
        self.epoch = 50
        self.batch_size = 100
        self.learning_rate = 0.001
        self.train_file = "./savemodel/" + model.name + ".ckpt"
        print("+++++" + self.train_file)

        #dataset
        self.mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

        #models
        self.input = tf.placeholder("float",[None,784])
        self.label = tf.placeholder("float",[None,10])
        self.model = model
        self.predict = self.model(self.input)
        #loss
        cross_entropy = -tf.reduce_sum(self.label*tf.log(self.predict))
        self.cross_entropy = cross_entropy
        #train
        #optimizer = tf.train.AdamOptimizer(self.learning_rate)
        optimizer = tf.train.GradientDescentOptimizer(self.learning_rate)
        self.train_step = optimizer.minimize(self.cross_entropy)
        #acc
        correct_prediction = tf.equal(tf.argmax(self.label,1),tf.argmax(self.predict,1))
        self.accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
        #sess
        
        #gpu_options = tf.GPUOptions(allow_growth=True)
        self.sess = tf.Session() #config=tf.ConfigProto(gpu_options=gpu_options)
    
    def __call__(self,input_img):
        pass
        # saver = tf.train.Saver()
        # init = tf.global_variables_initializer()       
        # with tf.Session() as sess:
        #     sess.run(init)
        #     if os.path.exists([self.train_file,'.meta']):
        #         saver.restore(sess,self.train_file)
 
    def train(self):
        epoch_list = []
        loss_list = []
        acc_list = []
        
        saver = tf.train.Saver()

        if os.path.exists(self.train_file+".meta"):
            saver.restore(self.sess,self.train_file)
            print("++++++ Restored the stored model! ++++++")
        else:
            self.sess.run(tf.global_variables_initializer())
            print("++++++ Auto initialize the paras! ++++++")

        with self.sess as sess:            
            total_batch = int(self.mnist.train.num_examples/self.batch_size)
            for epoch in range(self.epoch):

                myloss,myacc = sess.run([self.cross_entropy,self.accuracy],feed_dict={self.input:self.mnist.validation.images,self.label:self.mnist.validation.labels})
                epoch_list.append(epoch)
                loss_list.append(myloss)
                acc_list.append(myacc)
                print("step %d ,acc %g"%(epoch,myacc))

                for i in range(total_batch):
                    batch_x, batch_y = self.mnist.train.next_batch(self.batch_size)
                    sess.run(self.train_step,feed_dict={self.input:batch_x, self.label:batch_y})
                
            saver.save(sess,self.train_file)

        plt.figure(1)
        plt.plot(epoch_list,loss_list/np.max(loss_list),'r-',label='loss')
        plt.plot(epoch_list,acc_list,'b-',label='acc')
        plt.legend()
        plt.show()        


def main():

   
    # modle = myClassifyer(mutiDense())
    # modle.train()  

    method2 = mutiCNN()
    method2.isTrain = True
    # method2.epoch = 50
    modle2 = myClassifyer(method2) 
    modle2.train()

if __name__ == '__main__':
    main()