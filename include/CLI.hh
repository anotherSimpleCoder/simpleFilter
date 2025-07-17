//
// Created by abav on 17.07.2025.
//

#ifndef CLI_HH
#define CLI_HH
#include <string>
#include <unordered_map>

namespace CLI {
    struct Arguments {
        std::string fileName;
        float filterFrequency;
    };

    enum ArgumentProperty {
        FILE,
        FREQUENCY
    };

    extern std::unordered_map<std::string, ArgumentProperty> propertyMap;
    void run(int argc, char** argv);
};
#endif //CLI_HH
