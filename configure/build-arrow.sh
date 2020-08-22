#!/bin/bash

mkdir arrow/cpp/build
cmake -S arrow/cpp/  -B arrow/cpp/build \
                -DARROW_BUILD_SHARED=OFF \
                -DARROW_BUILD_STATIC=ON \
                -DARROW_CSV=ON \
                -DARROW_DEPENDENCY_SOURCE=BUNDLED \
                -DARROW_DEPENDENCY_USE_SHARED=OFF \
                -DARROW_PARQUET=ON


make  -j2 arrow/cpp/build/Makefile

make install -C arrow/cpp/build/

