add_library(Player
    Player.cc
)

target_link_libraries(Player
        portaudio_static
)