cmake_minimum_required(VERSION 3.30)
project(simpleFilter)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        portaudio
        GIT_REPOSITORY https://github.com/PortAudio/portaudio
        GIT_TAG master
)
FetchContent_MakeAvailable(portaudio)

FetchContent_Declare(
        sndfile
        GIT_REPOSITORY https://github.com/libsndfile/libsndfile
        GIT_TAG master
)
FetchContent_MakeAvailable(sndfile)

FetchContent_Declare(
        abseil-cpp
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp
        GIT_TAG master
)
FetchContent_MakeAvailable(abseil-cpp)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)