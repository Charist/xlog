cmake_minimum_required (VERSION 3.1)
project (xlog)

MESSAGE(STATUS "-------------------------------------------------------------------------------------")
MESSAGE(STATUS "CMAKE_SYSTEM is ${CMAKE_SYSTEM}")
MESSAGE(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
MESSAGE(STATUS "CMAKE_SYSTEM_VERSION is ${CMAKE_SYSTEM_VERSION}")
MESSAGE(STATUS "CMAKE_SYSTEM_PROCESSOR is ${CMAKE_SYSTEM_PROCESSOR}")
MESSAGE(STATUS "CMAKE_GENERATOR is ${CMAKE_GENERATOR}")
MESSAGE(STATUS "CMAKE_C_COMPILER_ID is ${CMAKE_C_COMPILER_ID}")
MESSAGE(STATUS "CMAKE_CXX_COMPILER_ID is ${CMAKE_CXX_COMPILER_ID}")
MESSAGE(STATUS "PROJECT_SOURCE_DIR is ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "PROJECT_BINARY_DIR is ${PROJECT_BINARY_DIR}")
MESSAGE(STATUS "CMAKE_CXX_FLAGS is ${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

MESSAGE(STATUS "CMAKE_SHARED_LIBRARY_PREFIX is ${CMAKE_SHARED_LIBRARY_PREFIX}")
MESSAGE(STATUS "CMAKE_SHARED_LIBRARY_SUFFIX is ${CMAKE_SHARED_LIBRARY_SUFFIX}")


MESSAGE(STATUS "-------------------------------------------------------------------------------------")

SET(CMAKE_CXX_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


IF (iOS_PROJECT)
	add_subdirectory(src)
ELSEIF (macOS_PROJECT)
	add_subdirectory(test)
ELSE()
	add_subdirectory(BASE/src)
	add_subdirectory(BASE/test)
ENDIF()

