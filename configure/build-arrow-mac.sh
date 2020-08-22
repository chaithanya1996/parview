#!/bin/bash

export CPATH=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
mkdir arrow/cpp/build
cmake -S arrow/cpp/  -B arrow/cpp/build \
                -DARROW_BUILD_SHARED=OFF \
                -DARROW_BUILD_STATIC=ON \
                -DARROW_COMPUTE=ON \
                -DARROW_CSV=ON \
                -DARROW_DATASET=ON \
                -DARROW_DEPENDENCY_SOURCE=BUNDLED \
                -DARROW_DEPENDENCY_USE_SHARED=OFF \
                -DARROW_PARQUET=ON \
                -DCMAKE_C_COMPILER=/usr/local/bin/gcc \
                -DCMAKE_CXX_COMPILER=/usr/local/bin/g++

make  arrow/cpp/build/Makefile

make install -C arrow/cpp/build/

