mkdir -p build
cmake -G "Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build .
cd build
ninja