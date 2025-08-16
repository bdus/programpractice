#!/bin/bash

# 构建镜像
docker build -t pytorch-cuda-devices .

# 启动容器，挂载GPU
docker run --rm --gpus all pytorch-cuda-devices