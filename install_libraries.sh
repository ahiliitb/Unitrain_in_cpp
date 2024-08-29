cd third_party
sudo apt update && sudo apt install -y cmake g++ wget unzip

# downloading torch
wget https://download.pytorch.org/libtorch/nightly/cpu/libtorch-shared-with-deps-latest.zip
unzip libtorch-shared-with-deps-latest.zip
rm -rf libtorch-shared-with-deps-latest.zip

# downloading opencv
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
rm -rf opencv.zip

# installing opencv and building it
mkdir -p build && cd build

# Configure
cmake  ../opencv-4.x
 
# Build
cmake --build .  # can also use make -j8

cd ../..