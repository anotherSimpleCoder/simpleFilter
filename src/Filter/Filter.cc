//
// Created by abav on 17.07.2025.
//
#include "Filter.hh"


#include <complex>
#include <math.h>

void Filter::filter(std::vector<float>& audio, float filterFrequency) {
    std::vector<std::complex<float>> frequencyBins;
    std::complex<float> j(0, 1);
    std::complex<float> negativeJ(0, -1);
    int N = audio.size();

    // Forward DFT
    for (int omega = 0; omega < N; omega++) {
        std::complex<float> sum(0, 0);

        for (int k = 0; k < N; k++) {
            float angle = 2.0f * M_PI * omega * k / static_cast<float>(N);
            sum += audio[k] * std::exp(negativeJ * angle);
        }

        frequencyBins.push_back(sum);
    }

    // Filtering - convert filterFrequency to bin index
    float sampleRate = 44100.0f; // Assuming 44.1kHz
    int cutoffBin = static_cast<int>(filterFrequency * N / sampleRate);

    for (int i = cutoffBin; i < N; i++) {
        frequencyBins[i] = 0;
    }

    // Inverse DFT
    for (int n = 0; n < N; n++) {
        std::complex<float> sum(0, 0);

        for (int k = 0; k < N; k++) {
            float angle = 2.0f * M_PI * k * n / static_cast<float>(N);
            sum += frequencyBins[k] * std::exp(j * angle);
        }

        audio[n] = sum.real() / static_cast<float>(N);
    }
}
