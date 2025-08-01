//
// Created by abav on 01.08.2025.
//

#ifndef FILTER_HH
#define FILTER_HH
#include <fftw3.h>
#include <vector>

class Filter {
    int N;                    // Signal length
    float* input;           // Input buffer
    fftwf_complex* fft_data;  // FFT output buffer
    float* output;          // Output buffer (filtered signal)
    fftwf_plan forward_plan;  // Forward FFT plan
    fftwf_plan inverse_plan;  // Inverse FFT plan

public:
    Filter(int signal_length);
    ~Filter();
    void filter(std::vector<float>& signal, double cutoff_freq, double sample_rate = 44100);
};
#endif //FILTER_HH
