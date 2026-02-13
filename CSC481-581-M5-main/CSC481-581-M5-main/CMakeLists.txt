cmake_minimum_required(VERSION 3.16)
project(SDL3Clock CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 QUIET CONFIG)
find_package(SDL3_ttf QUIET CONFIG)

if (TARGET SDL3::SDL3 AND TARGET SDL3_ttf::SDL3_ttf)
    message(STATUS "Using modern SDL3 + SDL3_ttf CMake targets")

    add_executable(main ./src/main.cpp)
    target_link_libraries(main PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)

else()
    message(STATUS "Falling back to pkg-config for SDL3")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3 REQUIRED sdl3)
    pkg_check_modules(SDL3TTF REQUIRED sdl3-ttf)

    add_executable(main ./src/main.cpp)

    target_include_directories(main PRIVATE
        ${SDL3_INCLUDE_DIRS}
        ${SDL3TTF_INCLUDE_DIRS}
    )

    target_link_libraries(main PRIVATE
        ${SDL3_LIBRARIES}
        ${SDL3TTF_LIBRARIES}
    )

    target_compile_options(main PRIVATE
        ${SDL3_CFLAGS_OTHER}
        ${SDL3TTF_CFLAGS_OTHER}
    )
endif()
