# semi-supervised
尝试在MNIST上实现半监督方法

baseline参见[link](../mnist_baseline/)

* supervised    文件夹中是监督的模型
* semi        中是半监督的模型
* lib     中是公共的类

## supervised

supervised 主要测试不同的分类模型

目录结构参考dff系列代码

symbols.py结构仿照gluon cv 的model_zoo

## semi

semi 主要实现不同模型的半监督训练

## lib

lib实现公共的类,比如

* dataset
