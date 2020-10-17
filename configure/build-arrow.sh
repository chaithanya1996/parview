#!/bin/bash

if [[ -z "${CPATH}" ]]; then
  echo $CPATH
else
  echo "CPATH Not found"
fi

echo "------------------------------"
echo $OSTYPE
echo "------------------------------"

if [ $OSTYPE = "darwin19" ] ; then
  export CPATH=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include
fi


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

make -j2 -C build/arrow
make install -C build/arrow

