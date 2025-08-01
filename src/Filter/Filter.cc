#include "Filter.hh"
#include <iostream>

Filter::Filter(int signal_length) : N(signal_length) {
    std::cout << "Setting up filter..." << std::endl;
    // Allocate memory for FFTW arrays
    input = fftwf_alloc_real(N);
    fft_data = fftwf_alloc_complex(N/2 + 1);  // Real FFT only needs N/2+1 complex values
    output = fftwf_alloc_real(N);

    // Create FFTW plans
    forward_plan = fftwf_plan_dft_r2c_1d(N, input, fft_data, FFTW_MEASURE);
    inverse_plan = fftwf_plan_dft_c2r_1d(N, fft_data, output, FFTW_MEASURE);
}

Filter::~Filter() {
    // Clean up FFTW resources
    fftwf_destroy_plan(forward_plan);
    fftwf_destroy_plan(inverse_plan);
    fftwf_free(input);
    fftwf_free(fft_data);
    fftwf_free(output);
}

void Filter::filter(std::vector<float>& signal, double cutoff_freq, double sample_rate) {
    std::cout << "Filtering..." << std::endl;
    // Copy input signal to FFTW input buffer
    for (int i = 0; i < N; i++) {
        input[i] = (i < signal.size()) ? signal[i] : 0.0f;
    }

    // Execute forward FFT
    fftwf_execute(forward_plan);

    // Apply lowpass filter in frequency domain
    int cutoff_bin = static_cast<int>((cutoff_freq / sample_rate) * N);

    for (int i = 0; i <= N/2; i++) {
        if (i > cutoff_bin) {
            // Zero out frequencies above cutoff
            fft_data[i][0] = 0.0;  // Real part
            fft_data[i][1] = 0.0;  // Imaginary part
        }
    }

    // Execute inverse FFT
    fftwf_execute(inverse_plan);

    // Copy and normalize output (FFTW inverse doesn't normalize)
    signal.resize(N);
    for (int i = 0; i < N; i++) {
        signal[i] = output[i] / N;
    }
}
