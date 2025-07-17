//
// Created by abav on 17.07.2025.
//
#include "CLI.hh"

#include <iostream>
#include <vector>
#include <absl/strings/str_split.h>

#include "FileReader.hh"
#include "Player.hh"

namespace CLI {
    std::unordered_map<std::string, ArgumentProperty> propertyMap = {
        {"file", FILE},
        {"freq", FREQUENCY}
    };
    void parseArgument(std::vector<std::string> splittedArgument, Arguments& arguments) {
        ArgumentProperty property = propertyMap[splittedArgument.at(0)];
        std::string value = splittedArgument[1];

        switch (property) {
            case FILE: {
                arguments.fileName = value;
                break;
            }

            case FREQUENCY: {
                arguments.filterFrequency = std::stof(value);
                break;
            }
        }
    }
    Arguments parseArguments(int argc, char** argv) {
        Arguments arguments{};
        std::vector<std::string> args{argv, argv + argc};

        if (args.size() < 3) {
            std::cerr << "Invalid usage!\n";
            std::cerr << "\tsimpleFilter file=<fileName> freq=<filterFrequency in Hz>\n";
        }

        for (std::string arg : args) {
            std::vector<std::string> splittedArgument = absl::StrSplit(arg, '=');

            if (splittedArgument.size() > 1) {
                parseArgument(splittedArgument, arguments);
            }
        }

        return arguments;
    }

    void run(int argc, char** argv) {
        Arguments arguments = parseArguments(argc, argv);
        std::vector<float> audio = FileReader::readFile(arguments.fileName);
        Player::play(audio);
    }
};