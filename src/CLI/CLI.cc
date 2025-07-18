//
// Created by abav on 17.07.2025.
//
#include "CLI/CLI.hh"
#include "CLI/Arguments.hh"

#include <iostream>
#include <vector>
#include <absl/strings/str_split.h>

#include "FileReader.hh"
#include "Filter.hh"
#include "Player.hh"

void CLI::run(int argc, char** argv) {
    Arguments::CLIArguments arguments = Arguments::parseArguments(argc, argv);
    std::vector<float> audio = FileReader::readFile(arguments.fileName);
/*
        std::cout << "Doing filtering..\n";
    Filter::filter(audio, arguments.filterFrequency);
    std::cout << "Done.\n";
*/
    Player::play(audio);
};