# CMakeList.txt : CMake project for My_Vector, include source and define
# project specific logic here.
#

# Add source to this project's executable.
include_directories(include)
add_executable (My_Vector "src/main.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET My_Vector PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
