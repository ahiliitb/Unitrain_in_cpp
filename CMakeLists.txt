cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(Unitrain_in_cpp)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third_party/opencv;${CMAKE_SOURCE_DIR}/third_party/libtorch")

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPENCV_CXX_FLAGS}")


include_directories(${Torch_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(basic_model src/basic_model.cpp)
target_link_libraries(basic_model ${TORCH_LIBRARIES} ${OpenCV_LIBS} opencv_core opencv_imgcodecs)
target_include_directories(basic_model PRIVATE ${Torch_INCLUDE_DIRS})
target_include_directories(basic_model PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_directories(basic_model PRIVATE ${CMAKE_PREFIX_PATH})
set_property(TARGET basic_model PROPERTY CXX_STANDARD 17)