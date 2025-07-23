cmake_minimum_required(VERSION 3.21)
project(munchkill)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Keep this for non-msvc compilers
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
	set(CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/x64-mingw-static/share" CACHE STRING "")
endif()

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(munchkill main.cpp)

target_link_libraries(munchkill PRIVATE fmt::fmt spdlog::spdlog)
