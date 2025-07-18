//
// Created by abav on 17.07.2025.
//

#ifndef ARGUMENTS_HH
#define ARGUMENTS_HH
#include <string>
#include <unordered_map>

namespace CLI {
    namespace Arguments {
        struct CLIArguments {
            std::string fileName;
            float filterFrequency;
        };

        enum CLIArgumentProperty {
            FILE,
            FREQUENCY
        };

        extern std::unordered_map<std::string, CLIArgumentProperty> propertyMap;
        CLIArguments parseArguments(int argc, char** argv);
    }
};
#endif //ARGUMENTS_HH
