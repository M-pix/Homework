

if (WIN32)
	
	set(GTEST_ROOT "C:/Users/deima/Documents/MyLibrary/googletest")
	set (GTEST_LIBRARIES ".../googletest/out/build/x64-Debug/lib")
	set (GTEST_LIBRARY "C:/Users/deima/Documents/MyLibrary/googletest/out/build/x64-Debug/lib/gtest.lib")
	set(GTEST_MAIN_LIBRARY "C:/Users/deima/Documents/MyLibrary/googletest/out/build/x64-Debug/lib/gtest_main.lib")
	set(GTEST_INCLUDE_DIR "C:/Users/deima/Documents/MyLibrary/googletest/googletest/include")
	
	find_package(GTest REQUIRED)
	
	include_directories(${GTEST_INCLUDE_DIR})

	include_directories(${CMAKE_SOURCE_DIR}/Image/include)
	
	add_executable(test_image src/test_image.cpp src/main.cpp ${CMAKE_SOURCE_DIR}/Image/src/Image.cpp)

	target_link_libraries(test_image ${GTEST_LIBRARIES} GTest::gtest_main)

endif(WIN32)


if (UNIX)

	set(GTEST_ROOT "../googletest")
	
	find_package(GTest REQUIRED)
	
	include_directories(${GTEST_INCLUDE_DIRS})

	include_directories(${CMAKE_SOURCE_DIR}/Image/include)
	
	add_executable(test_image  src/test_image.cpp src/main.cpp ${CMAKE_SOURCE_DIR}/Image/src/Image.cpp)
	
	target_link_libraries(test_image ${GTEST_LIBRARIES} pthread)

endif(UNIX)


add_test(NAME ImageTest_1 COMMAND test_image)
add_test(NAME ImageTest_2 COMMAND test_image)
add_test(NAME ImageTest_3 COMMAND test_image)
add_test(NAME ImageTest_4 COMMAND test_image)
add_test(NAME ImageTest_clone COMMAND test_image)
add_test(NAME ImageTest_copyTo COMMAND test_image)
add_test(NAME ImageTest_create COMMAND test_image)
add_test(NAME ImageTest_empty COMMAND test_image)
add_test(NAME ImageTest_realese COMMAND test_image)
add_test(NAME ImageTest_col COMMAND test_image)
add_test(NAME ImageTest_row COMMAND test_image)
add_test(NAME ImageTest_zeros COMMAND test_image)
add_test(NAME ImageTest_values COMMAND test_image)
add_test(NAME ImageTest_Mirror_horrizontal COMMAND test_image)
add_test(NAME ImageTest_Mirror_vertical COMMAND test_image)
add_test(NAME ImageTest_Rotate COMMAND test_image)

