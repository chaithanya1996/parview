#!/bin/bash

#if [ $OSTYPE = "darwin19" ] ; then
#  export CPATH=/Library/Developer/CommandLineTools/usr/include/c++/v1
#fi

mkdir -p build/arrow

cmake -S arrow/cpp/  -B build/arrow \
                -DARROW_BUILD_SHARED=OFF \
                -DARROW_BUILD_STATIC=ON \
                -DARROW_CSV=ON \
                -DARROW_DEPENDENCY_SOURCE=BUNDLED \
                -DARROW_DEPENDENCY_USE_SHARED=OFF \
                -DARROW_PARQUET=ON \
                -DARROW_WITH_BROTLI=ON \
                -DARROW_WITH_BZ2=ON \
                -DARROW_WITH_LZ4=ON \
                -DARROW_WITH_SNAPPY=ON \
                -DARROW_WITH_ZLIB=ON \
                -DARROW_WITH_ZSTD=ON

make -j3 -C build/arrow
make install -C build/arrow

