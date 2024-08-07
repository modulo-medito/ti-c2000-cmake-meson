# General project settings
project('ti_c2000', 'c',
  version : '1.0',
  default_options : [
    # 'b_lto=false',
    # 'b_asneeded=false',
    # 'b_lundef=false',
    # 'b_pch=false',
    # 'b_staticpic=false',
    # 'c_std=c99',
    # 'cpp_std=c++11'
    ],
  meson_version : '>=1.5.0')

# Global variables tracking sources and includes
c_args = []
c_link_args = []
project_src = []
project_inc = []
test_src = []
test_inc = []
link_deps = []

# find external programs from path (OS independant)
# size = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/size.exe')
# as = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000.exe')
# objcopy = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/ofd2000.exe')
# objdump = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/hex2000.exe')
# ld = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000.exe')

# C files recursivly search
found_src = run_command('./script/search_c.bat', check: false, env: 'P1=./src')
project_src += found_src.stdout().strip().split('\n')
found_src = run_command('./script/search_c.bat', check: false, env: 'P1=./platform/ti_c2000_tms320f280039c/src')
project_src += found_src.stdout().strip().split('\n')
message('meson.build: The C = ', project_src)

# ASM files recursivly search
found_src = run_command('./script/search_asm.bat', check: false, env: 'P1=./src')
project_src += found_src.stdout().strip().split('\n')
found_src = run_command('./script/search_asm.bat', check: false, env: 'P1=./platform/ti_c2000_tms320f280039c/src')
project_src += found_src.stdout().strip().split('\n')
message('meson.build: The ASM = ', project_src)

# Header files recursivly search
project_inc += './platform/ti_c2000_tms320f280039c/src/device/'
project_inc += './platform/ti_c2000_tms320f280039c/src/device/driverlib/'
project_inc += './platform/ti_c2000_tms320f280039c/src/device/driverlib/inc/'
project_inc += './src/'
project_inc += './src/bsw/os/'
project_inc += './src/bsw/drv/'
project_inc += './src/bsw/mcu/'
project_inc += './src/bsw/typedef/'
project_inc += './src/bsw/os/freertos/'
project_inc += './src/bsw/os/freertos/kernel/port/'
project_inc += './src/bsw/os/freertos/kernel/include/'

# Set compile flags - processor options
c_args += '-v28' # silicon_version
c_args += '-ml' # large_memory_model
c_args += '-mt' # unified_memory
c_args += '--cla_support=cla2'
c_args += '--float_support=fpu32'
c_args += '--tmu_support=tmu0'
c_args += '--vcu_support=vcrc'
# Set compile flags - optimization
c_args += '-O2' # opt_level
c_args += '--opt_for_speed=2' # opt_for_speed
c_args += '-Ooff' # opt_level
c_args += '--fp_mode=relaxed' # floating point mode
# Set compile flags - predefined symbols
c_args += '--define=LARGE_MODEL'
c_args += '--define=_FLASH'
c_args += '--define=DEBUG'
c_args += '--define=_LAUNCHXL_F280039C'
# Set compile flags - advanced debug options
c_args += '--symdebug:dwarf' # enable full symbolic DWARF debugging in out file
# Set compile flags - performance advicer
c_args += '--advice:performance=all' # show performance advice
# Set compile flags - diagnostic options
c_args += '-g' # treat diag id as warning
c_args += '--diag_warning=225' # treat diag id as warning
c_args += '--diag_wrap=off' # wrap diagnostic
# set(TOOLCHAIN_C_FLAGS "${TOOLCHAIN_C_FLAGS} --emit_warnings_as_errors") # treat diagnostic warnings as errors
c_args += '--display_error_number' # emit diag id numbers
c_args += '--verbose_diagnostics' # show error location with file line and pos
# Set compile flags - runtime model options
c_args += '--gen_func_subsections=on' # place each function in a separate subsection
c_args += '--abi=eabi' # application binary interface

# compile the main executable
main = executable('ti_c2000',
  project_src,
  name_suffix : 'out',
  c_args : c_args,
  link_args : [c_link_args],
  dependencies : link_deps,
  include_directories : [project_inc])
