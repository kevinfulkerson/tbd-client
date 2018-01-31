cmake_minimum_required(VERSION 2.8.11)

project(TBD)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(TBD_ROOT_DIR ${PROJECT_SOURCE_DIR})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# GLEW - currently hardcoded
if (WIN32)
	set(GLEW_LIBRARIES "C:/MinGW/lib/libglew32.dll.a")
	set(GLEW_INCLUDE_DIRS "C:/MinGW/include/GL")
elseif (UNIX)
	set(GLEW_LIBRARIES "/usr/lib/x86_64-linux-gnu/libGLEW.so")
	set(GLEW_INCLUDE_DIRS "/usr/include/GL")
endif (WIN32)

# OpenGL
find_package(OpenGL REQUIRED)

include_directories(${TBD_ROOT_DIR})

set(sourceFiles 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/engine/core/Engine.cpp
	${PROJECT_SOURCE_DIR}/src/engine/input/InputSystem.cpp
	${PROJECT_SOURCE_DIR}/src/engine/rendering/RenderingSystem.cpp)

add_executable(tbd-client ${sourceFiles})

if (UNIX)
    set_target_properties(tbd-client PROPERTIES SUFFIX ".out")
endif (UNIX)

target_link_libraries(tbd-client ${SDL2_LIBRARY})
target_link_libraries(tbd-client ${GLEW_LIBRARIES})
target_link_libraries(tbd-client ${OPENGL_LIBRARIES})
