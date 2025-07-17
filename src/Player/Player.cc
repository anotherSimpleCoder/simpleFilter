//
// Created by abav on 17.07.2025.
//
#include "Player.hh"
#include <stdexcept>
#include <portaudio.h>

void Player::play(std::vector<float>& samples) {
    //Initialize
    int err = Pa_Initialize();
    if (err != paNoError ) {
        throw std::runtime_error(Pa_GetErrorText(err));
    }


    //Play audio
    PaStream* stream;
    err = Pa_OpenDefaultStream(
        &stream,
        0,
        2,
        paFloat32,
        44100,
        256,
        [](
            const void* input,
            void* output,
            unsigned long frameCount,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags,
            void* userData
        ) {
            float* out = (float*) output;
            auto* sound = (std::vector<float>*) userData;

            for (int i = 0; i < frameCount; i++) {
                if (i < sound->size()) {
                    out[i * 2] = (*sound)[i];     // Left channel
                    out[i * 2 + 1] = (*sound)[i]; // Right channel (same as left)
                } else {
                    out[i * 2] = 0.0f;     // Silence when no more samples
                    out[i * 2 + 1] = 0.0f;
                }
            }
            return 0;
        },
        &samples
    );
    if (err != paNoError ) {
        throw std::runtime_error(Pa_GetErrorText(err));
    }

    err = Pa_StartStream(stream);
    if (err != paNoError ) {
        throw std::runtime_error(Pa_GetErrorText(err));
    }

    Pa_Sleep(60000);

    err = Pa_StopStream(stream);
    if (err != paNoError ) {
        throw std::runtime_error(Pa_GetErrorText(err));
    }

    err = Pa_Terminate();
    if (err != paNoError ) {
        throw std::runtime_error(Pa_GetErrorText(err));
    }
}
