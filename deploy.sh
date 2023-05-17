rm -rf build

mkdir build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE="C:/Gobble/CADT/PERSONAL/Backend_Oatpp/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

./Debug/main.exe