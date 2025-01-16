
rm ./build/app
cmake -S . -B build
cmake --build build
./build/app
