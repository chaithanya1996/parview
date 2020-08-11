cmake_minimum_required(VERSION 3.16)
project(parview)

set(CMAKE_CXX_STANDARD 14)
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Arrow REQUIRED)
add_executable(parview main.cpp util/ParseParquet.cpp util/ParseParquet.h)
target_link_libraries(parview  ${Boost_LIBRARIES}  arrow parquet)