add_library(FileReader
    FileReader.cc
)

target_link_libraries(FileReader
    SndFile::sndfile
)