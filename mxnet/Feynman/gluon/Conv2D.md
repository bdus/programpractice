# mxnet.gluon.Conv2D

## input
data: 4D input tensor with shape (batch_size, in_channels, height, width) when layout is NCHW. For other layouts shape is permuted accordingly.

## output
out: 4D output tensor with shape (batch_size, channels, out_height, out_width) when layout is NCHW. out_height and out_width are calculated as:

>out_height = floor((height+2*padding[0]-dilation[0]*(kernel_size[0]-1)-1)/stride[0])+1
out_width = floor((width+2*padding[1]-dilation[1]*(kernel_size[1]-1)-1)/stride[1])+1

```python
import mxnet as mx
from mxnet.gluon import nn, loss
from mxnet import initializer as init
from mxnet import ndarray as nd

img = nd.ones((7,3,224,224)) # batch_size, in_channels, height, width

# https://github.com/mzolfaghari/ECO-pytorch/blob/master/tf_model_zoo/ECO/ECO.yaml
net = nn.Sequential()
net.add(
    nn.Conv2D(64,(7,7),strides=(2,2),padding=(3,3)), # conv1_7x7_s2<=Convolution<=data
    nn.BatchNorm(),     # conv1_7x7_s2_bn<=BN<=conv1_7x7_s2
    nn.PReLU(alpha_initializer=init.Constant(0)), # conv1_7x7_s2_bn<=ReLU<=conv1_7x7_s2_bn
    nn.MaxPool2D(pool_size=(3,3),strides=2,padding=1) # pool1_3x3_s2<=Pooling<=conv1_7x7_s2_bn
    )

net.add(
    nn.Conv2D(64,(1,1)), # conv2_3x3_reduce<=Convolution<=pool1_3x3_s2
    nn.BatchNorm(), # conv2_3x3_reduce_bn<=BN<=conv2_3x3_reduce
    nn.PReLU(alpha_initializer=init.Constant(0)) #conv2_3x3_reduce_bn<=ReLU<=conv2_3x3_reduce_bn
)
net.add(
    nn.Conv2D(192,(3,3),padding=(1,1)), # conv2_3x3<=Convolution<=conv2_3x3_reduce_bn
    nn.BatchNorm(), #conv2_3x3_bn<=BN<=conv2_3x3
    nn.PReLU(alpha_initializer=init.Constant(0)), #conv2_3x3_bn<=ReLU<=conv2_3x3_bn
    nn.MaxPool2D(pool_size=(3,3),strides=2,padding=1) #pool2_3x3_s2<=Pooling<=conv2_3x3_bn
)

net.add(
    nn.Conv2D(64,(1,1))
)

net.initialize(init=init.Constant(1))
print(net)
ans = net(img)
print(ans.shape)

```