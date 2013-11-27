#!/bin/bash

PROJECT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}")" && pwd)

PROJECT_DIR=$( dirname $(echo $PROJECT_DIR | awk '{print $1}'))
export LD_LIBRARY_PATH="$PROJECT_DIR/lib:$LD_LIBRARY_PATH"
export PATH="$PROJECT_DIR/bin:$PATH"
