cmake_minimum_required(VERSION 3.30)
project(simpleFilter)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/portaudio)
include_directories(lib/portaudio/include)

add_subdirectory(lib/libsndfile)
include_directories(lib/libsndfile/include)

add_subdirectory(lib/abseil-cpp)
include_directories(lib/abseil-cpp)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)