#!/bin/sh

if [ ! -d deps/libxl ] ; then
  mkdir deps
  cd deps
  wget http://www.libxl.com/download/libxl.tar.gz
  tar zxf libxl.tar.gz
  rm -rf libxl.tar.gz
  mv libxl* libxl
  cd ..

  uname -i | grep "64" 1>/dev/null
  if [ "$?" -eq "0" ] ; then
    ARCHPATH="lib64"
  else
    ARCHPATH="lib"
  fi

  sudo cp deps/libxl/$ARCHPATH/libxl.so /usr/lib
fi