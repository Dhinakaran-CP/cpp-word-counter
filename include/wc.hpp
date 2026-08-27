#pragma once

#include <cstddef>
#include <fstream>
#include <string>

struct Flags{
    bool lines = false;
    bool words = false;
    bool bytes = false;
};

struct CountResult{
    std::size_t lines = 0;
    std::size_t words = 0;
    std::size_t bytes = 0;
};

//Function declaration. Note: No function body here , just the decalaration
CountResult count_stream(std::istream& file);