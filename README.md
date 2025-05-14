# datastructures-c

Simple data structures in C.

*Note: these are by no means the fastest data structures imaginable. Implementations have a wide variety of optimizations depending on the task, and my task was simplicity.*

# Building 

This repository uses [CMake](https://cmake.org/) as its build system:

```
mkdir build 
cd build 
cmake ..

cmake --build .
```

# Testing 

After running the cmake configuration above:

```
cmake --build .
ctest
```
