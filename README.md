# ccwc — High-Performance Word Count (wc) in Modern C++

[![Language](https://img.shields.io/badge/C%2B%2B-17%2F20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Build](https://img.shields.io/badge/Build-CMake-orange.svg)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

A fast, cross-platform rebuild of the classic Unix `wc` (word count) utility built from first principles in modern C++.

Designed for high-throughput stream processing with zero-overhead state tracking, stream polymorphism, and 64 KB chunk-buffered I/O.

---

## Key Features

- **POSIX-Compliant Counting:**
  - `-l`: Count line breaks (`\n`)
  - `-w`: Count words separated by whitespace (`std::isspace`)
  - `-c`: Count total raw bytes
- **Stream Polymorphism:** Seamlessly processes disk files or piped terminal streams via `std::istream&` abstraction.
- **High-Throughput Buffered I/O:** Uses a 64 KB chunk buffer (`std::array<char, 65536>`) to minimize syscalls and maximize CPU cache hits.
- **Deterministic Finite State Machine (FSM):** O(N) single-pass word parser with zero allocations during scanning.
- **Cross-Platform:** Builds identically on Windows (MinGW/MSVC), Linux, and macOS via modern target-based CMake.

---

## Performance & Benchmarks

Benchmarked on Windows 11 using PowerShell `Measure-Command`:

| Dataset Size | Lines | Words | Raw Bytes | Execution Time | Throughput |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Medium Dataset** | 100,000 | 900,000 | 4.40 MB | **~0.05 s (52 ms)** | **~84.6 MB/s** |
| **Large Dataset** | 1,000,000 | 9,000,000 | 45.00 MB | **~0.57 s (578 ms)** | **~78.0 MB/s** |

### Why is it fast?
1. **No Single-Byte I/O Overhead:** Naive character-by-character reading (`file.get(ch)`) incurs function-call overhead 45 million times. `ccwc` reads 65,536-byte blocks in a single shot.
2. **CPU Cache Localization:** Inner processing loops operate on contiguous memory in the CPU's ultra-fast L1 cache.
3. **Zero Heap Allocations:** The counting loop performs zero dynamic memory allocations (`new` / `malloc`), avoiding heap contention.

---

## Project Structure

```text
.
├── CMakeLists.txt        # Target-based CMake build configuration
├── include/
│   └── wc.hpp            # Interface declarations & Result structs
├── src/
│   ├── wc.cpp            # Core counting engine & buffered FSM
│   └── main.cpp          # CLI parser, flag handling, & orchestration
└── README.md
```

---

## Build Instructions

### Prerequisites

- C++17 or higher compatible compiler (GCC, Clang, or MSVC)
- CMake 3.15+

### Compilation Steps

```bash
# 1. Clone the repository
git clone https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git
cd YOUR_REPO_NAME

# 2. Generate build system
mkdir build && cd build
cmake ..

# 3. Compile the binary
cmake --build .
```

The compiled binary `ccwc` (or `ccwc.exe` on Windows) will be available in the `build/` directory.

---

## Usage

### 1. Process a File on Disk

```bash
# Default mode (prints lines, words, bytes, and filename)
./ccwc path/to/file.txt

# Selective flags
./ccwc -l path/to/file.txt         # Lines only
./ccwc -w path/to/file.txt         # Words only
./ccwc -c path/to/file.txt         # Bytes only
./ccwc -l -w path/to/file.txt      # Lines and words
```

### 2. Process Standard Input (Piping)

`ccwc` automatically reads from stdin when no filename is passed:

**Linux / macOS:**
```bash
cat /usr/include/stdio.h | ./ccwc -l
```

**Windows PowerShell:**
```powershell
Get-Content file.txt | .\ccwc.exe -l -w
```

---

## License

This project is licensed under the MIT License — see the LICENSE file for details.
