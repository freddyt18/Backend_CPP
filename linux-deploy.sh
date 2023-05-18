mkdir build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .

chmod +x main
ls Debug
ls
./Debug/main