MESSAGE(STATUS "test PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "test PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

include_directories("${PROJECT_SOURCE_DIR}/deps/googletest/googletest/include"
                    "${PROJECT_SOURCE_DIR}/deps/googletest/googlemock/include"
					"${PROJECT_SOURCE_DIR}/deps/poco/Foundation/include"
                    "${PROJECT_SOURCE_DIR}/BASE/src")

IF (WIN32)
    IF (MSVC14)
        link_directories(${PROJECT_SOURCE_DIR}/libs/windows/vs2015 ${PROJECT_BINARY_DIR}/libs)
    ELSEIF (MSVC10)
        # ......
    ENDIF (MSVC14)
ELSEIF (APPLE)
    link_directories(${PROJECT_SOURCE_DIR}/libs/macos ${PROJECT_BINARY_DIR}/libs)
    # ......
ELSEIF (UNIX)
    # 待添加
ELSEIF (MINGW)
    # 待添加
ENDIF (WIN32)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
MESSAGE(STATUS "----------------- EXECUTABLE_OUTPUT_PATH: ${EXECUTABLE_OUTPUT_PATH}")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#add_definitions(-std=c++11)
#add_compile_options(-std=c++11)

file (GLOB ROOT_TEST_SOURCES "${PROJECT_SOURCE_DIR}/BASE/test/*.cpp")
source_group("" FILES ${ROOT_TEST_SOURCES})

file (GLOB LOG_TEST_SOURCES "${PROJECT_SOURCE_DIR}/BASE/test/log/*.cpp")
source_group("log" FILES ${LOG_TEST_SOURCES})

add_executable(RunAllTest 
	${ROOT_TEST_SOURCES} 
	${LOG_TEST_SOURCES} 
)

IF (WIN32)
	target_link_libraries(RunAllTest xlog debug gtestmdd optimized gtestmd 
						debug gmockmdd optimized gmockmd)
ELSEIF (APPLE)
    target_link_libraries(RunAllTest gmock xlog PocoFoundation stdc++.6.0.9 c++.1)
ENDIF (WIN32)



# set_property(TARGET RunAllTest PROPERTY FOLDER "executables")
