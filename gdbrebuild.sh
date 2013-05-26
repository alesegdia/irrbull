#!/usr/bin/env sh

proj_home=~/Dropbox/Universidad/RV/rvfinal

cd $proj_home/build
cmake -DCMAKE_BUILD_TYPE=Debug .. && make

