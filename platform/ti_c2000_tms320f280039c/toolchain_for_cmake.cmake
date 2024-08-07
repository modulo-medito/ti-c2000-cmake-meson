################################################################################
# TI toolchain
################################################################################
# User specified paths
# Compiler path
# set(TOOLCHAIN_CPL_DIR "D:/user_chc/4_app/ccs/2_ws/ti/ccs1271/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS")
# Device root path
# set(TOOLCHAIN_SDK_DIR "D:/user_chc/4_app/ccs/2_ws/ti/c2000/C2000Ware_4_02_00_00/device_support/f28003x")

# The name of the target operating system, if your target is an embedded system
# without an OS, set CMAKE_SYSTEM_NAME to "Generic"
# Presetting CMAKE_SYSTEM_NAME this way instead of being detected,
# automatically causes CMake to consider the build a cross-compiling build and
# the CMake variable CMAKE_CROSSCOMPILING will be set to TRUE.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Set toolchain environment
# This is a list of the directories that contain the target environment.
# Each of the directories listed here will be prepended to each of the search
# directories of every find command.
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_CPL_DIR})
# Toolchain paths
find_program(TI_GCC     NAMES cl2000   PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)
find_program(TI_CXX     NAMES cl2000   PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)
find_program(TI_AS      NAMES cl2000   PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)
find_program(TI_AR      NAMES ar2000   PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)
find_program(TI_OBJCOPY NAMES ofd2000  PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)
find_program(TI_OBJDUMP NAMES hex2000  PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)
find_program(TI_SIZE    NAMES size2000 PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)
find_program(TI_LD      NAMES cl2000   PATHS ${TOOLCHAIN_CPL_DIR}/bin NO_DEFAULT_PATH)

# Set executables settings, this must be done before any language is set
set(CMAKE_C_COMPILER   ${TI_GCC})
set(CMAKE_CXX_COMPILER ${TI_CXX})
set(AS                 ${TI_AS})
set(AR                 ${TI_AR})
set(OBJCOPY            ${TI_OBJCOPY})
set(OBJDUMP            ${TI_OBJDUMP})
set(SIZE               ${TI_SIZE})
set(LD                 ${TI_LD})

# Sources
file(GLOB_RECURSE TOOLCHAIN_SRC
    ${CMAKE_CURRENT_LIST_DIR}/src/*.[ch]
    ${CMAKE_CURRENT_LIST_DIR}/src/device/*.[ch]
    ${CMAKE_CURRENT_LIST_DIR}/src/device/*.asm
    ${CMAKE_CURRENT_LIST_DIR}/src/device/driverlib/*.[ch]
    )

# Set compile flags - processor options
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} -v28") # silicon_version
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} -ml") # large_memory_model
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} -mt") # unified_memory
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --cla_support=cla2")
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --float_support=fpu32")
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --tmu_support=tmu0")
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --vcu_support=vcrc")
# Set compile flags - optimization
# set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} -O2") # opt_level
# set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --opt_for_speed=2") # opt_for_speed
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} -Ooff") # opt_level
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --fp_mode=relaxed") # floating point mode
# Set compile flags - predefined symbols
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --define=LARGE_MODEL")
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --define=_FLASH")
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --define=DEBUG")
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --define=_LAUNCHXL_F280039C")
# Set compile flags - advanced debug options
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --symdebug:dwarf") # enable full symbolic DWARF debugging in out file
# Set compile flags - performance advicer
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --advice:performance=all") # show performance advice
# Set compile flags - diagnostic options
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} -g") # treat diag id as warning
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --diag_warning=225") # treat diag id as warning
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --diag_wrap=off") # wrap diagnostic
# set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --emit_warnings_as_errors") # treat diagnostic warnings as errors
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --display_error_number") # emit diag id numbers
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --verbose_diagnostics") # show error location with file line and pos
# Set compile flags - runtime model options
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --gen_func_subsections=on") # place each function in a separate subsection
set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --abi=eabi") # application binary interface
# Final
set(TOOLCHAIN_C_FLAGS ${TOOLCHAIN_C_FLAGS} CACHE STRING "platform config c flags")
set(TOOLCHAIN_CXX_FLAGS ${TOOLCHAIN_C_FLAGS} CACHE STRING "platform config cxx flags")

# Set link options
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--stack_size=0x300")
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--warn_sections")
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--reread_libs")
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--diag_wrap=off")
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--display_error_number")
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--rom_model")
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--define=_FLASH")
set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--define=_LAUNCHXL_F280039C")
# set(TOOLCHAIN_LNK_OPT ${TOOLCHAIN_LNK_OPT} "--entry_point=code_start")

# Set toolchain default compile include directory, added to INCLUDE_DIRECTORIES
# directory property for the current CMakeLists file.
set(TOOLCHAIN_INC ${TOOLCHAIN_INC} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/device)
set(TOOLCHAIN_INC ${TOOLCHAIN_INC} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/device/driverlib)
set(TOOLCHAIN_INC ${TOOLCHAIN_INC} PUBLIC ${TOOLCHAIN_CPL_DIR}/include)
set(TOOLCHAIN_INC ${TOOLCHAIN_INC} PUBLIC ${TOOLCHAIN_CPL_DIR}/include/stlport)
# set(TOOLCHAIN_INC ${TOOLCHAIN_INC} PUBLIC ${TOOLCHAIN_SDK_DIR}/common/include)
# set(TOOLCHAIN_INC ${TOOLCHAIN_INC} PUBLIC ${TOOLCHAIN_SDK_DIR}/headers/include)

# Specify the search path of the linking libraries
set(TOOLCHAIN_LNK ${TOOLCHAIN_LNK} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/lsl)
set(TOOLCHAIN_LNK ${TOOLCHAIN_LNK} PUBLIC ${TOOLCHAIN_CPL_DIR}/lib)
# set(TOOLCHAIN_LNK ${TOOLCHAIN_LNK} PUBLIC ${TOOLCHAIN_SDK_DIR}/headers/cmd)
# set(TOOLCHAIN_LNK ${TOOLCHAIN_LNK} PUBLIC ${TOOLCHAIN_SDK_DIR}/common/cmd)

# Specify the libraries in the linking libraries search path
set(TOOLCHAIN_LIB ${TOOLCHAIN_LIB} 28003x_generic_flash_lnk.cmd)
set(TOOLCHAIN_LIB ${TOOLCHAIN_LIB} rts2800_fpu32_eabi.lib)
set(TOOLCHAIN_LIB ${TOOLCHAIN_LIB} -llibc.a)
