---
title: [mxnet] getting start
---


# init

## 参考资料

入门参考了教程：

* 【60-Minute Gluon Crash Course External】 [[link]](http://gluon-crash-course.mxnet.io/)
* 【PDF: Gluon 动⼿学深度学习】[[link]](http://zh.gluon.ai/gluon_tutorials_zh.pdf)

60min教程写的还是比较流畅的，认真读刚好一个小时能够看完，加上写就要久一点，中间ndarray的部分可以参考PDF，然后教程以经典的深度helloWord为主线，介绍了用mxnet实现FashionMnist的LeNet分类，包括模型的定义，初始化，训练，参数保存，使用预训练模型和GPU高性能训练。

进一步可以继续阅读官网的其他教程和PDF的后几章节，进度快的话十个小时可以搞定。


## install

[download link](http://mxnet.incubator.apache.org/install/)

或者

参考PDF中的conda安装方式
```shell
mkdir xx && cd xx

wget -c https://zh.gluon.ai/gluon_tutorials_zh.zip

unzip x.zip

conda config ％换源

conda env create 0f environment.yml

source activate gluon

jupyter notebook

```

# ndarray

>MXNet’s primary tool for storing and transforming data. If you’ve worked with NumPy before, you’ll notice that a NDArray is, by design, similar to NumPy’s multi-dimensional array.

## 基本运算

nd的操作和np还是比较相似的
具体参考[官方[link]](https://gluon-crash-course.mxnet.io/ndarray.html) 和PDF Chapter2




