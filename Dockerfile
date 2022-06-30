FROM ubuntu:18.04 as env


RUN groupdel dialout

ENV DEBIAN_FRONTEND=noninteractive


RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    libssl-dev \
    zlib1g-dev \
    dos2unix \
    doxygen \
    graphviz \
    libc6-dbg \
    valgrind \
    git \
    libomp-dev \
    cmake \
    wget \
    curl



ARG USER_ID
ARG GROUP_ID
ARG DEP_DIR
ARG SRC_DIR

ENV DEP_DIR=/${DEP_DIR}
RUN echo ${DEP_DIR}
ENV SRC_DIR=/${SRC_DIR}
RUN echo ${SRC_DIR}

RUN addgroup --gid $GROUP_ID user 
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

RUN mkdir -p ${SRC_DIR}
RUN mkdir -p ${DEP_DIR}

RUN mkdir -p /home/user
WORKDIR /home/user/repo

#this would have to change when production comes because its very vulnerable
User user

