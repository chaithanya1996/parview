cmake_minimum_required(VERSION 3.16)
project(parview)

option(ARROW_LINK_SHARED "Link to the Arrow shared library" ON)

set(CMAKE_CXX_STANDARD 11)
set(ARROW_LINK_SHARED OFF)
set(Boost_USE_STATIC_LIBS   ON)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Arrow REQUIRED)

message(STATUS "Arrow version: ${ARROW_VERSION}")
message(STATUS "Arrow SO version: ${ARROW_FULL_SO_VERSION}")

add_executable(parview main.cpp util/ParseParquet.cpp util/ParseParquet.h)

if (ARROW_LINK_SHARED)
    target_link_libraries(parview   ${Boost_LIBRARIES}  parquet arrow_shared )
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(parview   ${Boost_LIBRARIES}  parquet arrow_static Threads::Threads  )
endif()


