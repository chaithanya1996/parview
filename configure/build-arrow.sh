#!/bin/bash

if [ $OSTYPE = "darwin19" ] ; then
  export CPATH=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
fi

mkdir -p build/arrow
mkdir -p build/arrow_build
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
                -DARROW_WITH_ZSTD=ON \
		-DCMAKE_INSTALL_PREFIX=build/arrow_build

make -j2 -C build/arrow
make install -C build/arrow

export LIBRARY_PATH=build/arrow_build
