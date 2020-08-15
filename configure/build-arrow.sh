#!/bin/bash

mkdir arrow/build
cmake -S arrow/  -B arrow/build \
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
                -DORC_SOURCE=BUNDLED

make -j2 arrow/build/Makefile

make install -C arrow/build/

