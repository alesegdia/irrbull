#!/usr/bin/env sh

proj_home=~/Dropbox/irrbull

cd $proj_home/build
cmake -DCMAKE_BUILD_TYPE=Debug .. && make

