add_library(FileWriter
    FileWriter.cc
)

target_link_libraries(FileWriter
    sndfile
)