cmake_minimum_required(VERSION 3.17)
project(server)

set(CMAKE_CXX_STANDARD 14)

add_executable(server main.cpp)
if(WIN32)
    target_link_libraries(server wsock32 ws2_32)
endif()