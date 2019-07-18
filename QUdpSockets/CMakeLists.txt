cmake_minimum_required(VERSION 3.0.0)

project(QUdpSockets VERSION 0.1 LANGUAGES ASM C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ansi -pedantic")

# Include Qt libraries
find_package(Qt5Core)
find_package(Qt5Network)

# Custom includes
set(LIBS_DIR  "../../01_Libs/")

set(CUSTOM_HEADERS "")
#list(APPEND CUSTOM_HEADERS "${LIBS_DIR}/ThirdParty/include/")

# Custom sources
set(CUSTOM_SOURCES "")
#list(APPEND CUSTOM_SOURCES "${LIBS_DIR}ThreadPool/include/*.cpp")

# Includes
#include_directories("${LIBS_DIR}Utils/include/")

######################################Include everuthing src##################################
file(GLOB_RECURSE Proj_SOURCES ${CUSTOM_SOURCES} "src/*.cpp" "src/*.c" "include/*.c" "include/*.cpp")
file(GLOB_RECURSE Proj_HEADERS ${CUSTOM_HEADERS} "src/*.h" "src/*.hpp" "include/*.h" "include/*.hpp")

set( Proj_INCLUDE_DIRS "include/")
foreach (_headerFile ${Proj_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND Proj_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Proj_INCLUDE_DIRS)
include_directories(${Proj_INCLUDE_DIRS})
link_directories(${Proj_INCLUDE_DIRS})
##############################################################################################

add_executable (${PROJECT_NAME} ${Proj_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Proj_INCLUDE_DIRS})

# C++ Libs
target_link_libraries(${PROJECT_NAME} stdc++)
# Qt Libs
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Network)
