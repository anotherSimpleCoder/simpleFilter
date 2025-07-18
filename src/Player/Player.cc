//
// Created by abav on 17.07.2025.
//
#include "Player.hh"

#include <atomic>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <portaudio.h>

#define SAMPLE_SIZE 256


struct AudioCtx {
    std::vector<float>& samples;
    std::atomic<size_t> currentIndex{0};

    AudioCtx(std::vector<float>& s) : samples(s) {}
};

int consumer(
    const void* input,
    void* output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData
) {
    float* out = static_cast<float*>(output);
    AudioCtx* audioCtx = static_cast<AudioCtx*>(userData);

    for (unsigned long i = 0; i < frameCount; i++) {
        size_t index = audioCtx->currentIndex.fetch_add(1);

        if (index < audioCtx->samples.size()) {
            out[i] = audioCtx->samples[index];
        } else {
            out[i] = 0.0f; // Silence when we've played all samples
        }
    }

    return audioCtx->currentIndex.load() >= audioCtx->samples.size() ? paComplete : paContinue;
}

void Player::play(std::vector<float>& samples) {
    // Initialize PortAudio
    int err = Pa_Initialize();
    if (err != paNoError) {
        throw std::runtime_error(Pa_GetErrorText(err));
    }

    AudioCtx audioCtx(samples);

    // Open stream
    PaStream* stream;
    err = Pa_OpenDefaultStream(
        &stream,
        0,          // input channels
        1,          // output channels
        paFloat32,  // sample format
        44100,      // sample rate
        256,        // frames per buffer
        consumer,   // callback
        &audioCtx   // user data
    );

    if (err != paNoError) {
        Pa_Terminate();
        throw std::runtime_error(Pa_GetErrorText(err));
    }

    // Start stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        Pa_CloseStream(stream);
        Pa_Terminate();
        throw std::runtime_error(Pa_GetErrorText(err));
    }

    // Wait for stream to complete
    while (Pa_IsStreamActive(stream)) {
        Pa_Sleep(100);
    }

    // Cleanup
    Pa_CloseStream(stream);
    Pa_Terminate();
}