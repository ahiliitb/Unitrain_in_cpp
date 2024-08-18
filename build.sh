rm -rf build
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=$PWD/../third_party/libtorch ..
make -j4