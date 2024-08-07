################################################################################
# Notes
################################################################################
# rmdir /s /q build
# mkdir build
# cmake -S ./ -B ./build
#   -G "Unix Makefiles"
#   -DCMAKE_TOOLCHAIN_FILE="../cmake/ti_toolchain.cmake"
#   -DCMAKE_MAKE_PROGRAM="C:/ti/ccs1260/ccs/utils/bin/gmake"
# cd build
# C:/ti/ccs1260/ccs/utils/bin/gmake -j 20 all -O
cmake_minimum_required(VERSION 3.25)

################################################################################
# Cmake options
################################################################################
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR "Unix Makefiles")
option(TREAT_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)

################################################################################
# Toolchain
################################################################################
include(${CMAKE_CURRENT_LIST_DIR}/platform/ti_c2000_tms320f280039c/toolchain_for_cmake.cmake)

################################################################################
# Project settings
################################################################################
# Set project, PROJECT_NAME is set in the build_cmake.bat
# set(PROJECT_NAME "ti_c2000")
project(${PROJECT_NAME} C ASM)

#-------------------------------------------------------------------------------
# Set your codes path here
#-------------------------------------------------------------------------------
set(SRC_PATH ${SRC_PATH}        ${CMAKE_CURRENT_LIST_DIR}/src)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/drv)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/mcu)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos/kernel)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos/kernel/include)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/typedef)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos/kernel/port)
set(SRC_PATH ${SRC_PATH}/*.[ch] ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos/kernel/port)
set(SRC_PATH ${SRC_PATH}/*.asm)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/drv)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/mcu)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos/kernel)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos/kernel/include)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/typedef)
set(INC_PATH ${INC_PATH} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/bsw/os/freertos/kernel/port)

# Sources
# GLOB_RECURSE will traverse all the subdirectories of the matched directory
# and match the files.
# Use GLOB instead for refined path specification.
file(GLOB SOURCES
    ${SRC_PATH}
    )

# Add to executable
add_executable(${PROJECT_NAME}
    ${TOOLCHAIN_SRC}
    ${SOURCES}
    )

# Specify cmake flags
set(CMAKE_C_FLAGS   "${TOOLCHAIN_C_FLAGS}")
set(CMAKE_ASM_FLAGS "${TOOLCHAIN_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${TOOLCHAIN_CXX_FLAGS}")

# Set link options
target_link_options(${PROJECT_NAME} BEFORE PUBLIC ${TOOLCHAIN_LNK_OPT})

# Set compiler include directories
target_include_directories(${PROJECT_NAME}
    ${TOOLCHAIN_INC}
    ${INC_PATH}
    )

# Specify the search path of the linking libraries
target_link_directories(${PROJECT_NAME}
    ${TOOLCHAIN_LNK}
    )

target_link_libraries(${PROJECT_NAME}
    ${TOOLCHAIN_LIB}
    )

# Set output file name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.out")
