#!/bin/bash

## Setting up the build environment
SDK="OpenWrt-SDK-15.05.1-ar71xx-generic_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64"
if ! [ -f "$SDK.tar.bz2" ]
then 
  wget  "http://ftp.stw-bonn.de/pub/openwrt/chaos_calmer/15.05.1/ar71xx/generic/OpenWrt-SDK-15.05.1-ar71xx-generic_gcc-4.8-linaro_uClibc-0.9.33.2.Linux-x86_64.tar.bz2" 
fi

if ! [ -d "tests/$SDK" ]
then
 tar -C tests -xf $SDK.tar.bz2 
fi

pwd=$(pwd)
#Linking packages
for file in `ls`; do
  ln -fs $pwd/$file ./tests/$SDK/package/$file
done  
