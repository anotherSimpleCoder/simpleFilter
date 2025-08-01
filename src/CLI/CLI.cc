#include "CLI/CLI.hh"
#include "CLI/Arguments.hh"

#include <vector>
#include <absl/strings/str_split.h>

#include "Filter.hh"
#include "FileReader.hh"
#include "FileWriter.hh"


void CLI::run(int argc, char** argv) {
    Arguments::CLIArguments arguments = Arguments::parseArguments(argc, argv);
    std::vector<float> audio = FileReader::readFile(arguments.fileName);
    Filter filter(audio.size());
    filter.filter(audio, arguments.filterFrequency);
    FileWriter::writeFile("filtered.wav", audio);
}