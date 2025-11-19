# CMakeList.txt : CMake project for FIFO, include source and define
# project specific logic here.
#
include_directories(include)
# Add source to this project's executable.
add_executable (FIFO "src/main.cpp"  "src/Thread_Safety_Queue.cpp" "src/FIFO.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FIFO PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
