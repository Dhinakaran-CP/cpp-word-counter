#include "wc.hpp"
#include <cctype>
#include <array>

CountResult count_stream(std::istream& in) {
    CountResult result;
    constexpr std::size_t BUFFER_SIZE = 64 * 1024;
    std::array<char, BUFFER_SIZE> buffer;

    bool in_word = false;

    while (in.read(buffer.data(), buffer.size()) || in.gcount() > 0) {
        std::streamsize bytes_read = in.gcount();
        result.bytes += static_cast<std::size_t>(bytes_read);

        for (std::streamsize i = 0; i < bytes_read; ++i) {
            unsigned char c = static_cast<unsigned char>(buffer[i]);

            if (c == '\n') {
                result.lines++;
            }

            //  Whitespace check (spaces, tabs, newlines, carriage returns)
            if (std::isspace(c)) {
                in_word = false;
            } else {
                if (!in_word) {
                    result.words++;
                    in_word = true;
                }
            }
        }
    }

    return result;
}