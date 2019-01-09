FROM mxnet/python:gpu_0.11.0
LABEL maintainer "Mrlicx@outlook.com"

# install python
RUN rm -rf /var/lib/apt/lists/*
RUN apt-get update && \
    #apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
            aptitude git vim make wget zip zsh pkg-config \
            build-essential checkinstall p7zip-full python-pip \
            python3-pip tmux ffmpeg i7z unrar htop cmake g++  \
            curl libopenblas-dev python-numpy python3-numpy \
            python python-tk idle python-pmw python-imaging \
            libjpeg8-dev libtiff5-dev libjasper-dev libpng12-dev \
            libtbb2 libtbb-dev  libdc1394-22-dev libavcodec-dev  \
            libavformat-dev libswscale-dev libv4l-dev libatlas-base-dev \
            gfortran

RUN echo 192.30.253.113 github.com >> /etc/hosts && \ 
 echo 151.101.41.194 github.global.ssl.fastly.net >> /etc/hosts

RUN apt-get -y install git wget unzip eog vlc python-pip python-dev python-tk libopenblas-dev cmake liblapacke-dev

RUN apt-get autoremove && \
    apt-get clean && \
    aptitude install -y python-dev 
   # update pip and setuptools
RUN  pip install --upgrade pip setuptools -i https://linux.xidian.edu.cn/mirrors/pypi/web/simple/

#curl -O https://bootstrap.pypa.io/get-pip.py && \
COPY ./get-pip.py ./get-pip.py
RUN     python3.5 get-pip.py && \
    rm get-pip.py

# install necessary libraries

RUN pip install Cython opencv-python==3.2.0.6 easydict==1.6 pyyaml Pillow matplotlib -i https://linux.xidian.edu.cn/mirrors/pypi/web/simple/
RUN sed -i 's/geteuid/getppid/' /usr/bin/vlc


# clone Deep-Feature-Flow
RUN git clone https://github.com/msracver/Deep-Feature-Flow.git
RUN cd Deep-Feature-Flow && chmod +x init.sh && ./init.sh


# clone mxnet
#RUN git clone --recursive https://github.com/dmlc/mxnet.git && cd mxnet && git checkout 62ecb60 && git submodule update
# copy files for segementation, can't do both at once
#RUN cp -r /Deep-Feature-Flow.git/rfcn/operator_cxx/* /mxnet/src/operator/contrib/
# copy files for detection 
RUN cp -r /Deep-Feature-Flow/dff_rfcn/operator_cxx/* /mxnet/src/operator/contrib/

# copy another config.mk I modified it just to support CUDA and CuDNN
COPY ./config.mk /mxnet/make
# compile mxnet
RUN cd mxnet && make clean && make -j8
RUN cd mxnet/python && python setup.py install

# place the trained model
COPY ./demo_model.zip /Deep-Feature-Flow/model 
RUN cd /Deep-Feature-Flow/model && unzip demo_model.zip && cp demo_model/* ./ && rm ./demo_model.zip && rm ./demo_model -rf


###############################################
###############################################

# 项目构建
WORKDIR /data
COPY . .

