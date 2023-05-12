# Desc: Install tools
apt-get update && apt-get install -y \
    build-essential \
    curl \
    git \
    vim \
    g++

# Other tools
apt-get install zip unzip tar

# Check if vcpgk is installed, if not installed, run the following commands
if [ ! -d "vcpkg" ]; then
    cd /
    # Install vcpkg
    git clone https://github.com/Microsoft/vcpkg.git && \
        ./vcpkg/bootstrap-vcpkg.sh && \
        export PATH=$(pwd):$PATH
fi

# Install Crow from vcpkg
vcpkg install crow

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

