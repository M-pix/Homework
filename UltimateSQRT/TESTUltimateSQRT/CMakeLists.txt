

if (WIN32)
	
	set(GTEST_ROOT "C:/Users/deima/Documents/MyLibrary/googletest")
	set (GTEST_LIBRARIES ".../googletest/out/build/x64-Debug/lib")
	set (GTEST_LIBRARY "C:/Users/deima/Documents/MyLibrary/googletest/out/build/x64-Debug/lib/gtest.lib")
	set(GTEST_MAIN_LIBRARY "C:/Users/deima/Documents/MyLibrary/googletest/out/build/x64-Debug/lib/gtest_main.lib")
	set(GTEST_INCLUDE_DIR "C:/Users/deima/Documents/MyLibrary/googletest/googletest/include")
	
	find_package(GTest REQUIRED)
	
	include_directories(${GTEST_INCLUDE_DIR})
	include_directories(include)
	include_directories(${CMAKE_SOURCE_DIR}/UltimateSQRT/include)
	
	add_executable(TESTUltimateSQRT src/TESTUltimateSQRT.cc  src/TESTUltimateSQRTSFINAE.cc src/main.cc)

	target_link_libraries(TESTUltimateSQRT ${GTEST_LIBRARIES} GTest::gtest_main)

endif(WIN32)


if (UNIX)

	set(GTEST_ROOT "../googletest")
	
	find_package(GTest REQUIRED)
	
	include_directories(${GTEST_INCLUDE_DIRS})
	include_directories(include)
	include_directories(${CMAKE_SOURCE_DIR}/Image/include)
	
	add_executable(test_image  src/test_image.cpp src/main.cpp ${CMAKE_SOURCE_DIR}/Image/src/Image.cpp)
	
	target_link_libraries(test_image ${GTEST_LIBRARIES} pthread)

endif(UNIX)


add_test(NAME UltimateSQRT COMMAND testUltimateSQRT)


