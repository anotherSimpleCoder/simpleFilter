cmake_minimum_required(VERSION 3.30)
project(simpleFilter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

include(FetchContent)

FetchContent_Declare(
        sndfile
        GIT_REPOSITORY https://github.com/libsndfile/libsndfile
        GIT_TAG master
)
FetchContent_MakeAvailable(sndfile)

FetchContent_Declare(
        abseil-cpp
        URL https://github.com/abseil/abseil-cpp/releases/download/20250512.1/abseil-cpp-20250512.1.tar.gz
        URL_HASH SHA256=9b7a064305e9fd94d124ffa6cc358592eb42b5da588fb4e07d09254aa40086db
)
FetchContent_MakeAvailable(abseil-cpp)

FetchContent_Declare(
        fftw3
        URL https://www.fftw.org/fftw-3.3.10.tar.gz
        URL_HASH MD5=8ccbf6a5ea78a16dbc3e1306e234cc5c
)
set(ENABLE_FLOAT ON CACHE BOOL "Enable single precision" FORCE)
FetchContent_MakeAvailable(fftw3)


include_directories("${fftw3_SOURCE_DIR}/api")
include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)