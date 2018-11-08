---
title: 【docker】install
---


# install docker-ce && nvidia-docker
环境 ubuntu

## docker-ce
这一步需要梯子/ipv6hosts
https://blog.csdn.net/chxw098/article/details/79741586

## nvidia-docker

https://github.com/NVIDIA/nvidia-docker

# 改dockerfile
参考
https://github.com/AIChallenger/AI_Challenger_2018/tree/master/Evaluation/short_video_real_time_classification_eval


基础镜像 Linux 16.04 CUDA8.0
参考
https://hub.docker.com/r/nvidia/cuda/
8.0-cudnn6-devel, 8.0-cudnn6-devel-ubuntu16.04 (8.0/devel/cudnn6/Dockerfile)


# build

 sudo nvidia-docker build -t tf_image .

 
 https://hub.docker.com/r/tensorflow/tensorflow/
 
 
 $ docker run --runtime=nvidia -it -p 8888:8888 tensorflow/tensorflow:latest-gpu

# referencs

https://blog.csdn.net/chxw098/article/details/79741586

http://www.dataguru.cn/article-12564-1.html