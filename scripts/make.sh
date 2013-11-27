#!/bin/bash

MY_PWD=`pwd`
export ZMQ="$HOME/zmq"
export CZMQ="$HOME/zmq"


PROJECT_DIR="$(dirname $(dirname $(readlink -m $0)))"
DO_INSTALL=0
if [ "$1" = "recreate" ];then
  shift
  echo -n "-- Doing cleaning "
  rm -Rf $PROJECT_DIR/build $PROJECT_DIR/bin $PROJECT_DIR/lib
  if [ "$?" = "0" ];then
    echo "[ OK ]"
  else
    echo "[ FAILED ]"
    exit 1
  fi
fi

if [ "$1" = "install" ];then
  shift
  DO_INSTALL="1"
fi

test -d $PROJECT_DIR/build || mkdir -p $PROJECT_DIR/build


cd $PROJECT_DIR/build

test -f Makefile ||  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="$PROJECT_DIR" ../

CMD="nice -n 15"
CMD="$CMD make $*"
$CMD || { RET=$?
  rm -Rf $PROJECT_DIR/bin $PROJECT_DIR/lib
  exit $RET
}

if [ "$DO_INSTALL" = "1" ];then
  CMD="nice -n 15"
  CMD="$CMD make install"
  $CMD || exit $?
fi

cd $MY_PWD
