#!/bin/sh

export LD_LIBRARY_PATH=./lib/:${LD_LIBRARY_PATH}
./demo $1
