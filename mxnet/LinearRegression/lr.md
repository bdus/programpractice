---
title: [mxnet] Linear regression
---

# model

讲线性回归的经典例子就是房价预测，房屋面积$x_1$,房龄为$x_2$，售价$y$
我们利用线性回归模型进行建模，得到房价的预测$\hat{y}$：
$$
    \hat{y} = x_1w_1 + x_2w_2 + b
$$

然后我们收集房价和房屋面积、房龄的真实数据，也就是对整体的采样，然后建模用于估计总体。

假设我们采集的样本数为 $n$，索引为 $i$ 的样本的特征为 $x^{(i)}_1$,$x^{(i)}_2$，标签为 $y^{(i)}$。对于索引为 $i$ 的房屋，线性回归模型的房屋价格预测表达式为

$$
\hat{y}^{(i)} = x_1^{(i)} w_1 + x_2^{(i)} w_2 + b.
$$

具体的loss和优化请参考[[link]](http://zh.gluon.ai/chapter_deep-learning-basics/linear-regression.html)

# vector
将样本矢量化：

$$
%\begin{split}\begin{aligned}
\hat{y}^{(1)} = x_1^{(1)} w_1 + x_2^{(1)} w_2 + b, \\
\hat{y}^{(2)} = x_1^{(2)} w_1 + x_2^{(2)} w_2 + b, \\
\hat{y}^{(3)} = x_1^{(3)} w_1 + x_2^{(3)} w_2 + b. 
%\end{aligned}\end{split}
$$

