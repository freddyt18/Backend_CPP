# Installation

## VCPKG

First, we need to install VCPKG. 

> VCPKG is a package manager for C++ libraries. It's a great tool that makes it easy to install and manage C++ libraries on Windows, Linux, and MacOS.

Here's how you can install Crow on your Windows machine using VCPKG:

1. Clone the VCPKG repository: `git clone https://github.com/microsoft/vcpkg.git`
2. Run the bootstrap script: `.\vcpkg\bootstrap-vcpkg.bat`
3. Integrate VCPKG: `.\vcpkg\vcpkg integrate install`

## Crow

Now that we have VCPKG installed, we can install Crow:

Assuming VCPKG is installed globally:

1. Install Crow: `vcpkg install crow`
2. Integrate Crow: `vcpkg integrate project`

## CMakeLists.txt

Now that we have Crow installed, we need to add it to our CMakeLists.txt file in order to build our project.

The content of the CMakeLists.txt file should look like this:

```
cmake_minimum_required(VERSION 3.26)

project(main)

find_package(Crow CONFIG REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC Crow::Crow)
```

## Build

Now that we have Crow installed and added to our CMakeLists.txt file, we can build our project by running the following commands:

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="path/to/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .
```

In this case, the path to VCPKG:
```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="C:/Gobble/CADT/PERSONAL/Backend_Oatpp/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .
```
