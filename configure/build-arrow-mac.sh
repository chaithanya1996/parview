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
                -DARROW_FILESYSTEM=ON \
                -DARROW_HDFS=ON \
                -DARROW_JEMALLOC=ON \
                -DARROW_JSON=ON \
                -DARROW_ORC=ON \
                -DARROW_PARQUET=ON \
                -DARROW_PLASMA=ON \
                -DARROW_WITH_BROTLI=ON \
                -DARROW_WITH_BZ2=ON \
                -DARROW_WITH_LZ4=ON \
                -DARROW_WITH_SNAPPY=ON \
                -DARROW_WITH_ZLIB=ON \
                -DARROW_WITH_ZSTD=ON \
                -DORC_SOURCE=BUNDLED \
                -DCMAKE_C_COMPILER=/usr/local/bin/gcc-9.3.0 \
                -DCMAKE_CXX_COMPILER=/usr/local/bin/g++-9.3.0

make  arrow/cpp/build/Makefile

make install -C arrow/cpp/build/

