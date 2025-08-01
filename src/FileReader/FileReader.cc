//
// Created by abav on 17.07.2025.
//
#include "FileReader.hh"

#include <iostream>
#include <sndfile.h>

std::vector<float> FileReader::readFile(std::string filePath) {
    SF_INFO fileInfo;
    SNDFILE* audioFile = sf_open(filePath.c_str(), SFM_READ, &fileInfo);
    
    const auto fileAudio = new float[fileInfo.frames];
    sf_read_float(audioFile, fileAudio, fileInfo.frames);
    sf_close(audioFile);

    std::vector<float> result {fileAudio, fileAudio + fileInfo.frames};
    return result;
}
