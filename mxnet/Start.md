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

％换源　conda config 

conda env create -f environment.yml

source activate gluon

jupyter notebook

```

# ndarray

>MXNet’s primary tool for storing and transforming data. If you’ve worked with NumPy before, you’ll notice that a NDArray is, by design, similar to NumPy’s multi-dimensional array.

## 基本运算

nd的操作和np还是比较相似的
具体参考[官方[link]](https://gluon-crash-course.mxnet.io/ndarray.html) 和PDF Chapter2

## 数据创建

```python

from mxnet import nd

x = nd.arange(12)
x.shape
x.size
x = x.reshape((3,4))
x = nd.arange(12).reshape((3,-1))

nd.zeros((2,3))
nd.ones((2,3))

nd.array([[1,2,3],[2,3,4],[4,5,6]])

nd.random.normal(0,1,shape=(3,4))

```

## 运算


```python
from mxnet import nd

x = nd.arange(12).reshape((3,-1))
y = nd.ones((3,4))

x + y
x * y
x / y
y.exp()
nd.dot(x,y.T)
# 合并多个ndarray （分别在行和列上）

x,y,nd.concat(x,y,dim=0)
# (
#  [[  0.   1.   2.   3.]
#   [  4.   5.   6.   7.]
#   [  8.   9.  10.  11.]]
#  <NDArray 3x4 @cpu(0)>, 
#  [[ 1.  1.  1.  1.]
#   [ 1.  1.  1.  1.]
#   [ 1.  1.  1.  1.]]
#  <NDArray 3x4 @cpu(0)>, 
#  [[  0.   1.   2.   3.]
#   [  4.   5.   6.   7.]
#   [  8.   9.  10.  11.]
#   [  1.   1.   1.   1.]
#   [  1.   1.   1.   1.]
#   [  1.   1.   1.   1.]]
#  <NDArray 6x4 @cpu(0)>)

x,y,nd.concat(x,y,dim=1)
# (
#  [[  0.   1.   2.   3.]
#   [  4.   5.   6.   7.]
#   [  8.   9.  10.  11.]]
#  <NDArray 3x4 @cpu(0)>, 
#  [[ 1.  1.  1.  1.]
#   [ 1.  1.  1.  1.]
#   [ 1.  1.  1.  1.]]
#  <NDArray 3x4 @cpu(0)>, 
#  [[  0.   1.   2.   3.   1.   1.   1.   1.]
#   [  4.   5.   6.   7.   1.   1.   1.   1.]
#   [  8.   9.  10.  11.   1.   1.   1.   1.]]
#  <NDArray 3x8 @cpu(0)>)

x == y

# [[ 0.  1.  0.  0.]
#  [ 0.  0.  0.  0.]
#  [ 0.  0.  0.  0.]]
# <NDArray 3x4 @cpu(0)>

y.sum()
# [ 12.]
# <NDArray 1 @cpu(0)>

y.sum().asscalar()#转换为Python的标量
# 12.0

```

## 广播机制

```python
a = nd.arange(3).reshape((3, 1))
b = nd.arange(2).reshape((1, 2))
# (
# [[0.]
# [1.]
# [2.]]
# <NDArray 3x1 @cpu(0)>,
# [[0. 1.]]
# <NDArray 1x2 @cpu(0)>)

# 由于 a 和 b 分别是 3 ⾏ 1 列和 1 ⾏ 2 列的矩阵，如果要计算 a+b，那么 a 中第⼀列的三个元
# 素被⼴播（复制）到了第⼆列，而 b 中第⼀⾏的两个元素被⼴播（复制）到了第⼆⾏和第三⾏。
# 如此，我们就可以对两个 3 ⾏ 2 列的矩阵按元素相加。
a + b

# [[0. 1.]
# [1. 2.]
# [2. 3.]]
# <NDArray 3x2 @cpu(0)>

```

## 索引

```python

x[1:3]

#指定 NDArray 中需要访问的单个元素的位置，重新赋值
x[1, 2] = 9
#截取⼀部分元素，并为它们重新赋值
x[1:2, :] = 12

```

此外还有内存操作和NDArray 和 NumPy 相互变换，见PDF Chapter 2