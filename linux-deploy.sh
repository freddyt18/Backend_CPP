rm -rf build
mkdir build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .

chmod +x main
./main