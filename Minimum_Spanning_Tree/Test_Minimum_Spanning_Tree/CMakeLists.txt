

if (WIN32)
	
	set(GTEST_ROOT "C:/Users/deima/Documents/MyLibrary/googletest")
	set (GTEST_LIBRARIES ".../googletest/out/build/x64-Debug/lib")
	set (GTEST_LIBRARY "C:/Users/deima/Documents/MyLibrary/googletest/out/build/x64-Debug/lib/gtest.lib")
	set(GTEST_MAIN_LIBRARY "C:/Users/deima/Documents/MyLibrary/googletest/out/build/x64-Debug/lib/gtest_main.lib")
	set(GTEST_INCLUDE_DIR "C:/Users/deima/Documents/MyLibrary/googletest/googletest/include")
	
	find_package(GTest REQUIRED)
	
	include_directories(${GTEST_INCLUDE_DIR})

	include_directories(${CMAKE_SOURCE_DIR}/Minimum_Spanning_Tree/include)
	
	add_executable(test_minimum_spanning_tree src/Test_File.cpp src/Test_Tree.cpp src/main.cpp  ${CMAKE_SOURCE_DIR}/Minimum_Spanning_Tree/src/Minimum_Spanning_Tree.cpp ${CMAKE_SOURCE_DIR}/Minimum_Spanning_Tree/src/File.cpp)
	#add_executable(test_minimum_spanning_tree ${CMAKE_SOURCE_DIR}/Minimum_Spanning_Tree/src/File.cpp ${CMAKE_SOURCE_DIR}/Minimum_Spanning_Tree/src/Position.cpp)#new

	target_link_libraries(test_minimum_spanning_tree ${GTEST_LIBRARIES} GTest::gtest_main)

endif(WIN32)


if (UNIX)

	set(GTEST_ROOT "../googletest")
	
	find_package(GTest REQUIRED)
	
	include_directories(${GTEST_INCLUDE_DIRS})

	include_directories(${CMAKE_SOURCE_DIR}/Minimum_Spanning_Tree/include)
	
	add_executable(test_minimum_spanning_tree  src/Test_Tree.cpp src/main.cpp ${CMAKE_SOURCE_DIR}/Minimum_Spanning_Tree/src/Minimum_Spanning_Tree.cpp)
	
	#add_executable(${CMAKE_SOURCE_DIR} Minimum_Spanning_Tree/src/File.cpp Minimum_Spanning_Tree/src/Position)

	target_link_libraries(test_minimum_spanning_tree ${GTEST_LIBRARIES} pthread)

endif(UNIX)

add_test(NAME Test_tree COMMAND test_minimum_spanning_tree)
add_test(NAME Test_file COMMAND test_minimum_spanning_tree)





