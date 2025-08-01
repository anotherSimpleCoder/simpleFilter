add_library(Filter
    Filter.cc
)

target_link_libraries(Filter
    fftw3f
)