MESSAGE(STATUS "src PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "src PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

include_directories("${PROJECT_SOURCE_DIR}/BASE/src"
					"${PROJECT_SOURCE_DIR}/BASE/src/log"
					"${PROJECT_SOURCE_DIR}/BASE/src/utility"
					"${PROJECT_SOURCE_DIR}/deps/poco/Foundation/include"
					"${PROJECT_SOURCE_DIR}/deps/poco/JSON/include")

# https://cmake.org/Wiki/CMake_Useful_Variables
IF (WIN32)
    IF (MSVC14)
        link_directories(${PROJECT_SOURCE_DIR}/libs/vs2015 ${PROJECT_BINARY_DIR}/libs)
    ELSEIF (MSVC10)
        # ......
    ENDIF (MSVC14)
ELSEIF (APPLE)
    include_directories("${PROJECT_SOURCE_DIR}/libs/iOS/include")
    link_directories(${PROJECT_SOURCE_DIR}/libs/iOS ${PROJECT_BINARY_DIR}/lib)
ELSEIF (UNIX)
    # 待添加
ELSEIF (MINGW)
    # 待添加
ENDIF (WIN32)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
MESSAGE(STATUS "----------------- LIBRARY_OUTPUT_PATH: ${LIBRARY_OUTPUT_PATH}")


file (GLOB LOG_SOURCES
    "${PROJECT_SOURCE_DIR}/BASE/src/log/*.cpp"
    "${PROJECT_SOURCE_DIR}/BASE/src/log/*.h")
source_group("log" FILES ${LOG_SOURCES})

file (GLOB UTILITY_SOURCES
    "${PROJECT_SOURCE_DIR}/BASE/src/utility/*.cc"
    "${PROJECT_SOURCE_DIR}/BASE/src/utility/*.h")
source_group("utility" FILES ${UTILITY_SOURCES})


add_library(xlog STATIC
	${UTILITY_SOURCES}
	${LOG_SOURCES}
	)

IF (WIN32)
	target_link_libraries(xlog debug PocoFoundationd optimized PocoFoundation)
ELSEIF (APPLE)
    target_link_libraries(xlog crypto ssl curl)
ENDIF (WIN32)


set_property(TARGET xlog PROPERTY FOLDER "libraries")
