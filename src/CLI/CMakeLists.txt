add_library(CLI
    CLI.cc
)

target_link_libraries(CLI
    FileReader
    Player
    absl::strings
)