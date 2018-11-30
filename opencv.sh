#!/bin/bash

# Script to install opencv2 along with opencv_contrib
# Kyle Cheung
# derived from https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html

# required
apt-get update
apt-get install build-essential
apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
apt-get install libopencv-dev

# optional
apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff5-dev libdc1394-22-dev

cd ~
mkdir opencv
cd opencv/
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd opencv/
mkdir build
cd build/

# cmake with extra modules
cmake -D CMAKE_INSTALL_PREFIX=/usr/local -D CMAKE_BUILD_TYPE=Release -D OPENCV_EXTRA_MODULES_PATH=~/opencv/opencv_contrib/modules ..

# make with multiple threads
make -j7

make install
