FROM ubuntu

# Set root user
USER root

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Install tools
RUN apt-get update && apt-get install -y \
 build-essential \
 curl \
 git \
 wget \
 g++

# Other tools
RUN apt-get install -y zip unzip tar

# Install vcpkg
RUN cd / && \ 
    git clone https://github.com/Microsoft/vcpkg.git && \
    cd vcpkg && \
    chmod +x bootstrap-vcpkg.sh && \
    ./bootstrap-vcpkg.sh

ENV PATH="/vcpkg:${PATH}"

# Install CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.3/cmake-3.26.3-linux-x86_64.sh && \ 
    chmod +x *.sh && \
    ./cmake-3.26.3-linux-x86_64.sh --skip-license --prefix=/usr/local

ENV PATH="/usr/local/bin:${PATH}"

# Testing CMake
RUN cmake -version

# Install Crow from vcpkg
RUN cd / && vcpkg install crow

# cd to working directory
RUN cd /app

# Export the port
EXPOSE 18080

# Build and run the app
RUN mkdir build && cd build && cmake -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake" .. && cmake --build .

# Run the app
CMD ["./main"]
