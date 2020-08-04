cmake_minimum_required(VERSION 3.17)
project(parview)

set(CMAKE_CXX_STANDARD 14)
find_package(Boost COMPONENTS program_options REQUIRED )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_executable(parview main.cpp)
target_link_libraries(parview LINK_PUBLIC ${Boost_LIBRARIES})