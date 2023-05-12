FROM ubuntu

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Run the sh install script
RUN chmod +x tools.sh && ./tools.sh


# Build the app
RUN mkdir build && \ 
    cd build && \
    cmake -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake" .. && \
    cmake --build .


# Expose the app to 18080
EXPOSE 18080

# Set the default command to run the application
CMD ["./build/main"]

