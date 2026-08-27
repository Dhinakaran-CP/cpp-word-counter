# cpp-word-counter
A high-performance, command-line word count utility built from scratch in C++, mimicking the Unix wc tool with support for stdin stream polymorphism and custom performance metrics.

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

## License

This project is licensed under the MIT License — see the LICENSE file for details.
