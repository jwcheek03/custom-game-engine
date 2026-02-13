cmake_minimum_required(VERSION 3.16)
project(Module6_Multithreading)

set(CMAKE_CXX_STANDARD 17)

add_executable(multithreading_demo
    src/main.cpp
    src/JobSystem.cpp
    src/Networking.cpp 
)
