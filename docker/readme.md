# docker usage

## init

[[install-how-to]](./install.md)

[[nvidia docker hub]](https://hub.docker.com/r/nvidia/cuda/)

## man

* sudo nvidia-docker build -t eco:dockerfile .
* sudo nvidia-docker run -it -p 5000:22 eco:dockerfile /bin/bash
* sudo nvidia-docker commit 42a946551c61 eco:pytorch


* sudo nvidia-docker ps
* sudo nvidia-docker images -a

## opts

* NVIDIA GPU
>--runtime=nvidia -e NVIDIA_VISIBLE_DEVICES=0,1 --shm-size 8G

* ssh
> -p 127.0.0.1:5000:22 

* share disk
>-v `pwd`/UCF101:/workspace/data

* x11
>-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY -e GDK_SCALE -e GDK_DPI_SCALE

## instances

* [[eco]](./eco)

sudo nvidia-docker run --runtime=nvidia -e NVIDIA_VISIBLE_DEVICES=0,1 --shm-size 8G -it -p 127.0.0.1:5000:22 -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY -e GDK_SCALE -e GDK_DPI_SCALE -v `pwd`/UCF101:/workspace/data -v `pwd`/cache:/cache eco:ucf101_edit /bin/bash

* [[dff]](./dff)


## tips

* tinghua source
>https://mirrors4.tuna.tsinghua.edu.cn/ </br>
>https://mirrors6.tuna.tsinghua.edu.cn/ </br>
>https://mirrors.tuna.tsinghua.edu.cn/ 

pypi
>-i https://pypi.tuna.tsinghua.edu.cn/simple 

[anaconda](https://mirrors6.tuna.tsinghua.edu.cn/help/anaconda/)
>conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/ </br>
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/ </br>
conda config --set show_channel_urls yes </br>

* Anaconda 安装指定build编号的包
>conda search caffe </br>
>conda install caffe=1.0=py27_blas_openblas_201

