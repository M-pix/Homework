# CMakeList.txt : CMake project for Minimum_Spanning_Tree, include source and define
# project specific logic here.
#
include_directories (include)
# Add source to this project's executable.
add_executable (obeder src/main.cpp "src/File.cpp" "src/Str.cpp"  "src/Obeder.cpp" "src/Node.cpp")



# TODO: Add tests and install targets if needed.
