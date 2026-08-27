#include "wc.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    Flags flags;
    std::string filename = "";

    

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-l") {
            flags.lines = true;
        } else if (arg == "-w") {
            flags.words = true;
        } else if (arg == "-c") {
            flags.bytes = true;
        } else if (arg[0] == '-') {
            std::cerr << "Unknown flag: " << arg << "\n";
            return 1;
        } else {
            filename = arg;
        }
    }
    if (!flags.lines && !flags.words && !flags.bytes) {
        flags.lines = true;
        flags.words = true;
        flags.bytes = true;
    }

    CountResult result;
    
    if (filename.empty()){
        // no file is provided 
        result = count_stream(std::cin);
    }
    else {
        // file was provided -> open and read it 
        std::ifstream file(filename);
        if (!file.is_open()){
            std::cerr << "Error: Could not open file '"<< filename <<"'\n";
            return 1;
        }


        result = count_stream(file);
    }

    if (flags.lines) std::cout << result.lines << "\t";
    if (flags.words) std::cout << result.words << "\t";
    if (flags.bytes) std::cout << result.bytes << "\t";

    if (!filename.empty())std::cout << filename << "\n";

    return 0;
}