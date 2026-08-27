#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("big.txt");

    if (!file.is_open()) {
        std::cerr << "Could not create big.txt\n";
        return 1;
    }

    std::cout << "Generating 100,000 lines...\n";

    for (int i = 0; i < 100000; ++i) {
        
        file << "The quick brown fox jumps over the lazy dog\n";
    }

    std::cout << "Done!\n";
    return 0;
}