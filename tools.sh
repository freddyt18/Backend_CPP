# Desc: Install tools
apt-get update && apt-get install -y \
    build-essential \
    curl \
    git \
    vim \
    g++

# Other tools
apt-get install -y zip unzip tar

# Check if vcpgk is installed, if not installed, run the following commands
if [ ! -d "vcpkg" ]; then
    cd /
    # Install vcpkg
    git clone https://github.com/Microsoft/vcpkg.git && \
        cd vcpkg && \
        chmod +x bootstrap-vcpkg.sh && \
        ./bootstrap-vcpkg.sh && \
        export PATH=$(pwd):$PATH
fi

# Check if CMake is installed, if not installed, run the following commands
if [ ! -d "cmake-3.26.3-Linux-x86_64" ]; then
    # Install CMake
    curl -O https://github.com/Kitware/CMake/releases/download/v3.26.3/cmake-3.26.3-linux-x86_64.sh && \
        chmod +x *.sh && \
        ./cmake-3.26.3-linux-x86_64.sh --skip-license --prefix=/usr/local && \
        export PATH=$(pwd):$PATH
fi

# Testing CMake
cmake -version

# Install Crow from vcpkg
vcpkg install crow

# Build and run the app

# Check if build folder exists, if not, create itm it exists, delete it and create a new one
if [ -d "build" ]; then
    rm -rf build
fi
mkdir build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .

# Run the app
./main