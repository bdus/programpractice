#!/bin/bash

# 构建镜像
docker build -t pytorch-cuda-devices .

# 启动容器，挂载GPU
docker run --rm --gpus all pytorch-cuda-devices

# 本地运行
sudo docker run --rm --gpus all -it pytorch/pytorch:2.8.0-cuda12.9-cudnn9-runtime /bin/bash


docker commit <container_id> myapp_backup:v1
