cmake_minimum_required(VERSION 3.10)
project(ZMQMessagingApp)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

add_executable(server ./src/server.cpp)
add_executable(client ./src/client.cpp)

find_path(CPPZMQ_INCLUDE_DIR zmq.hpp)

if(NOT CPPZMQ_INCLUDE_DIR)
    message(FATAL_ERROR "cppzmq not found")
endif()

include_directories(${CPPZMQ_INCLUDE_DIR})

target_include_directories(server PRIVATE ${ZMQ_INCLUDE_DIRS})
target_include_directories(client PRIVATE ${ZMQ_INCLUDE_DIRS})

target_link_libraries(server PRIVATE ${ZMQ_LIBRARIES})
target_link_libraries(client PRIVATE ${ZMQ_LIBRARIES})
