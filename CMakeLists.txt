cmake_minimum_required(VERSION 3.16)
project(Strife)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost CONFIG REQUIRED COMPONENTS system)

add_executable(server server/main.cpp)
target_link_libraries(server Boost::system)

add_executable(client client/main.cpp)
target_link_libraries(client Boost::system)