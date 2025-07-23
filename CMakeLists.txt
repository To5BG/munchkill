cmake_minimum_required(VERSION 3.21)
project(munchkill)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(munchkill main.cpp)

target_link_libraries(munchkill PRIVATE fmt::fmt spdlog::spdlog)
