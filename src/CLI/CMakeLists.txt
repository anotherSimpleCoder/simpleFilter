add_library(CLI
    Arguments.cc
    CLI.cc
)

target_link_libraries(CLI
    FileReader
    FileWriter
    Filter
    absl::strings
)