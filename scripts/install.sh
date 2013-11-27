#!/bin/bash

MYZMQ_DIR="$(dirname $(dirname $(readlink -m $0)))"

[ -d $MYZMQ_DIR/etc ] || mkdir -p $YZMQ_DIR/etc
export PATH="$MYZMQ_DIR/bin:$PATH"
export LD_LIBRARY_PATH="$MYZMQ_DIR/lib:$LD_LIBRARY_PATH"

function MyMake() {
  git reset --hard
  git pull
  ./autogen.sh
  ./configure --prefix=$MYZMQ_DIR $* || exit 1
  make -j3 || exit 2
  make install || exit 3
}

[ -d $HOME/git/libzmq ] || git clone git://github.com/zeromq/libzmq.git
cd libzmq
MyMake --with-relaxed
cd ..

[ -d $HOME/git/czmq ] || git clone git://github.com/zeromq/czmq.git
cd czmq
MyMake --with-libzmq=$MYZMQ_DIR --with-relaxed
cd ..

cd $MYZMQ_DIR
scripts/make.sh install
