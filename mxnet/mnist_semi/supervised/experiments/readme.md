# experiments
该文件夹保存一系列../train.py或../test.py的历史版本,文件名不同

使用的时候复制(可能需要稍加修改)到上级目录运行

## simple
folder:[simple](./simple)

* train_simple.py
* test_simple.py
* symbols/symbols.py
* symbols/simple.py

这个是训练和使用
仿照gluoncv [modelzoo](https://github.com/dmlc/gluon-cv/blob/11eb654e938b32fd746ec5f72e09a44f35e99c7a/gluoncv/model_zoo/model_zoo.py)
结构写的../train.py和../test.py

仿照model_zoo目的是为了熟悉gluon和得到更好的修改模型 方便使用finetune过的网络

## finetune

folder:[finetune](./finetune)

* train_finetune.py
* test_finetune.py
* model_zoo的mobilenet0.25

使用gluoncv的模型在数据集上finetune 效果不错 gluoncv很好使