cmake_minimum_required(VERSION 3.12)

project(godot-openmpt CXX)

# BUILD CONFIG
include(ProcessorCount)
ProcessorCount(NB_PROCESSORS)

set(GODOT_BUILD_CORES ${NB_PROCESSORS})
set(GODOT_BUILD_PLATFORM "x11")
# include(SetProjectFlags)

# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules/cmake)
set(GODOT_MODULE_DIR ${PROJECT_SOURCE_DIR}/modules/)

set(GODOT_OPENMPT_DIR ${GODOT_MODULE_DIR}/libopenmpt)
set(GODOT_OPENMPT_SOURCE_DIR ${GODOT_OPENMPT_DIR}/src)
set(GODOT_OPENMPT_INCLUDE_DIR ${GODOT_OPENMPT_DIR}/include)

# GODOT
set(GODOT_DIR ${PROJECT_SOURCE_DIR}/godot)
set(GODOT_GDNATIVE_DIR ${GODOT_DIR}/modules/gdnative)
set(GODOT_SOURCE_DIR ${GODOT_DIR})
set(GODOT_INCLUDE_DIR ${GODOT_DIR})
set(GODOT_GDNATIVE_INCLUDE_DIR ${GODOT_GDNATIVE_DIR}/include)
#
set(GODOT_PLATFORM_INCLUDE_DIR ${GODOT_DIR}/platform/${GODOT_BUILD_PLATFORM})
#
set(GODOT_INCLUDE_DIRS
        ${GODOT_INCLUDE_DIR}
        ${GODOT_GDNATIVE_INCLUDE_DIR}
        # fix: Added for Intellisense
        ${GODOT_PLATFORM_INCLUDE_DIR}
        ${GODOT_DIR}
)
#
# OPENMPT
set(OPENMPT_DIR ${PROJECT_SOURCE_DIR}/openmpt)



# subdirs
add_subdirectory(${OPENMPT_DIR})

set(GODOT_OPENMPT_SOURCE_FILES
        ## source
        ${GODOT_OPENMPT_SOURCE_DIR}/godot_openmpt/Module.cpp
        ${GODOT_OPENMPT_SOURCE_DIR}/godot_openmpt/ModuleStream.cpp
        ${GODOT_OPENMPT_SOURCE_DIR}/godot_openmpt/ModuleStreamPlayback.cpp
        ${GODOT_OPENMPT_DIR}/register_types.cpp
)
set(GODOT_OPENMPT_INCLUDE_FILES
        ${GODOT_OPENMPT_INCLUDE_DIR}/godot_openmpt/Module.hpp
        ${GODOT_OPENMPT_INCLUDE_DIR}/godot_openmpt/ModuleStream.hpp
        ${GODOT_OPENMPT_INCLUDE_DIR}/godot_openmpt/ModuleStreamPlayback.hpp
        ${GODOT_OPENMPT_DIR}/register_types.hpp
)

# add_library(${PROJECT_NAME} STATIC ${GODOT_OPENMPT_FILES})

# target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_CXX_FLAGS})
# target_compile_features(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_CXX_STANDARD})

# target_include_directories(${PROJECT_NAME} PUBLIC ${GODOT_OPENMPT_INCLUDE_DIRS})

# target_link_libraries(${PROJECT_NAME} PUBLIC libopenmpt)

###
file(GLOB_RECURSE GODOT_SOURCE_FILES ${GODOT_DIR}/*.c?(pp))
file(GLOB_RECURSE GODOT_HEADER_FILES ${GODOT_DIR}/*.h?(pp))

find_program(SCONS_PROGRAMME scons)

if (NOT SCONS_PROGRAMME)
        message(FATAL_ERROR "SCons not found!")
endif(NOT SCONS_PROGRAMME)

add_custom_target(godot_scons
        ALL
        WORKING_DIRECTORY ${GODOT_DIR}
        COMMAND ${SCONS_PROGRAMME}
                custom_modules=${GODOT_MODULE_DIR}
                -j ${GODOT_BUILD_CORES}
                platform=${GODOT_BUILD_PLATFORM}
                libopenmpt_shared=no
        SOURCES ${GODOT_SOURCE_FILES} ${GODOT_INCLUDE_FILES} 
        USES_TERMINAL
)

add_executable(godot EXCLUDE_FROM_ALL 
        ${GODOT_SOURCE_FILES}
        ${GODOT_INCLUDE_FILES}
        #
        ${GODOT_OPENMPT_SOURCE_FILES}
        ${GODOT_OPENMPT_INCLUDE_FILES}
        )

target_include_directories(godot SYSTEM PUBLIC
        ${GODOT_INCLUDE_DIRS}
        ${GODOT_OPENMPT_INCLUDE_DIR}
)

target_compile_features(godot PRIVATE cxx_std_20)

target_link_libraries(godot PUBLIC libopenmpt)