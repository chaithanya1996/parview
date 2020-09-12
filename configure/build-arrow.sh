#!/bin/bash

ls -l 
mkdir -p build/arrow
cmake -S arrow/cpp/  -B build/arrow \
                -DARROW_BUILD_SHARED=OFF \
                -DARROW_BUILD_STATIC=ON \
                -DARROW_CSV=ON \
                -DARROW_DEPENDENCY_SOURCE=BUNDLED \
                -DARROW_DEPENDENCY_USE_SHARED=OFF \
                -DARROW_PARQUET=ON


make -j4 ../build/arrow/Makefile

#make install -C arrow/cpp/build/

