//
// Created by abav on 17.07.2025.
//
//
// Created by abav on 17.07.2025.
//
#include "CLI/Arguments.hh"

#include <iostream>
#include <vector>
#include <absl/strings/str_split.h>

namespace CLI {
    namespace Arguments {
        std::unordered_map<std::string, CLIArgumentProperty> propertyMap = {
            {"file", FILE},
            {"freq", FREQUENCY}
        };

        void parseArgument(std::vector<std::string> splittedArgument, CLIArguments& arguments) {
            CLIArgumentProperty property = propertyMap[splittedArgument.at(0)];
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

        CLIArguments parseArguments(int argc, char** argv) {
            CLIArguments arguments{};
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
    }
};