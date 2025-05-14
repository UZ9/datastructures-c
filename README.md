# datastructures-c

Simple header-only data structures in C.

*Note: these are by no means the fastest data structures imaginable. Implementations have a wide variety of optimizations depending on the task, and my task was simplicity.*

# Usage 

All data structures and algorithms in this repository are implemented as header-only libraries. Include the relevant header in your project from the `include` directory, and you're good to go.

# Building 

This repository uses [CMake](https://cmake.org/) as its build system:

```
mkdir build 
cd build 
cmake .. 
make 
make install
```
