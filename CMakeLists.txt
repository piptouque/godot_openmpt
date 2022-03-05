cmake_minimum_required(VERSION 3.12)

project(godot-openmpt CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules/cmake)

set(GODOT_OPENMPT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(GODOT_OPENMPT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(GODOT_CPP_DIR ${PROJECT_SOURCE_DIR}/godot-cpp)
set(OPENMPT_DIR ${PROJECT_SOURCE_DIR}/openmpt)

#
include(SetProjectFlags)

# subdirs
add_subdirectory(${GODOT_CPP_DIR})
add_subdirectory(${OPENMPT_DIR})

set(GODOT_OPENMPT_INCLUDE_DIRS
        ${GODOT_OPENMPT_INCLUDE_DIR}
        )

set(GODOT_OPENMPT_FILES
        # Cantina lib
        ## source
        ${GODOT_OPENMPT_SOURCE_DIR}/godot-openmpt/gdexample.cpp
        ## headers
        ${GODOT_OPENMPT_INCLUDE_DIR}/godot-openmpt/gdexample.hpp
        )

add_library(${PROJECT_NAME} STATIC ${GODOT_OPENMPT_FILES})

# target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_CXX_FLAGS})
# target_compile_features(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_CXX_STANDARD})

target_include_directories(${PROJECT_NAME} PUBLIC ${GODOT_OPENMPT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC
        godot-cpp
        libopenmpt
       )
