# CMakeList.txt : CMake project for UltimateSQRT, include source and define
# project specific logic here.
#
include_directories (include)
# Add source to this project's executable.
add_executable (UltimateSQRT "src/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET UltimateSQRT PROPERTY CXX_STANDARD 23)
endif()


# TODO: Add tests and install targets if needed.
