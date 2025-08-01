//
// Created by abav on 01.08.2025.
//
#include "FileWriter.hh"
#include <iostream>
#include <sndfile.h>

void FileWriter::writeFile(std::string fileName, std::vector<float> audioData) {
    SF_INFO sfInfo;
    sfInfo.channels = 1;
    sfInfo.samplerate = 44100;
    sfInfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

    SNDFILE* audioFile = sf_open(fileName.c_str(), SFM_WRITE, &sfInfo);
    std::cout << "Writing audio files..." << std::endl;
    sf_write_float(audioFile, audioData.data(), audioData.size());
    sf_close(audioFile);
}
