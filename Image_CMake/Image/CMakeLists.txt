# CMakeList.txt : CMake project for Image_CMake, include source and define
# project specific logic here.
#
#cmake_minimum_required(VERSION 3.12)
#project(Image)

include_directories (include)
# Add source to this project's executable.
add_executable (image src/main.cpp src/Image.cpp)

#if (CMAKE_VERSION VERSION_GREATER 3.12)
 # set_property(TARGET image PROPERTY CXX_STANDARD 20)
#endif()


# TODO: Add tests and install targets if needed.
