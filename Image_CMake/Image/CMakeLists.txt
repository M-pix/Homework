# CMakeList.txt : CMake project for Image_CMake, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.2)
project(Image)
# Add source to this project's executable.
add_executable (image main.cpp Image.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET image PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
