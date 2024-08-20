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
test_src = []
test_inc = []
link_deps = []
project_src = []
project_inc = []
c_files = []
asm_files = []

# find external programs from path (OS independant)
# size = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/size.exe')
# as = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000.exe')
# objcopy = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/ofd2000.exe')
# objdump = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/hex2000.exe')
# ld = find_program('C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000.exe')

# C files recursivly search
found_src = run_command('./script/search_c.bat', check: false, env: 'P1=./src')
c_files += found_src.stdout().strip().split('\n')
found_src = run_command('./script/search_c.bat', check: false, env: 'P1=./platform/ti_c2000_tms320f280039c/src')
c_files += found_src.stdout().strip().split('\n')
project_src += c_files
message('meson.build: The C = ', c_files)

# ASM files recursivly search
found_src = run_command('./script/search_asm.bat', check: false, env: 'P1=./src')
asm_files += found_src.stdout().strip().split('\n')
found_src = run_command('./script/search_asm.bat', check: false, env: 'P1=./platform/ti_c2000_tms320f280039c/src')
asm_files += found_src.stdout().strip().split('\n')
project_src += asm_files
message('meson.build: The ASM = ', asm_files)

# Header files recursivly search
project_inc += './platform/ti_c2000_tms320f280039c/src/device/'
project_inc += './platform/ti_c2000_tms320f280039c/src/device/driverlib/'
project_inc += './platform/ti_c2000_tms320f280039c/src/device/driverlib/inc/'
project_inc += './src/'
project_inc += './src/bsw/drv/'
project_inc += './src/bsw/mcu/'
project_inc += './src/bsw/os/'
project_inc += './src/bsw/os/freertos/'
project_inc += './src/bsw/os/freertos/kernel/include/'
project_inc += './src/bsw/os/freertos/kernel/port/'
project_inc += './src/bsw/typedef/'
project_inc += 'C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include/'
project_inc += 'C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib/'

# Set compile flags
c_args += '-v28' # processor: silicon_version
c_args += '-ml' # processor: large_memory_model
c_args += '-mt' # processor: unified_memory
c_args += '--cla_support=cla2'
c_args += '--float_support=fpu32'
c_args += '--tmu_support=tmu0'
c_args += '--vcu_support=vcrc'
# c_args += '-O2' # optimization: opt_level
# c_args += '--opt_for_speed=2' # optimization: opt_for_speed
c_args += '-Ooff' # optimization: opt_level
c_args += '--fp_mode=relaxed' # optimization: floating point mode
c_args += '--define=LARGE_MODEL' # predefined symbols
c_args += '--define=_FLASH' # predefined symbols
c_args += '--define=DEBUG' # predefined symbols
c_args += '--define=_LAUNCHXL_F280039C' # predefined symbols
c_args += '--symdebug:dwarf' # advanced debug options: enable full symbolic DWARF debugging in out file
c_args += '--advice:performance=all' # performance advicer: show performance advice
c_args += '-g' # diagnostic options
c_args += '--diag_warning=225' # diagnostic options: treat diag id as warning
c_args += '--diag_wrap=off' # diagnostic options: wrap diagnostic
# c_args += '--emit_warnings_as_errors' # treat diagnostic warnings as errors
c_args += '--display_error_number' # emit diag id numbers
c_args += '--verbose_diagnostics' # show error location with file line and pos
c_args += '--gen_func_subsections=on' # runtime model options: place each function in a separate subsection
c_args += '--abi=eabi' # runtime model options: application binary interface

# Set link flags - processor options
c_link_args += '--stack_size=0x300'
c_link_args += '--warn_sections'
c_link_args += '--reread_libs'
c_link_args += '--diag_wrap=off'
c_link_args += '--display_error_number'
c_link_args += '--rom_model'
c_link_args += '--define=_FLASH'
c_link_args += '--define=_LAUNCHXL_F280039C'

# Set libraries linking
# c_link_args += '-llibc.a'
# c_link_args += '-lrts2800_fpu32_eabi.lib'

# Dependency libraries
my_lib_path = 'C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib'
# my_lib = meson.get_compiler('c').find_library('libc.a', dirs: [my_lib_path], static: true)
# # my_lib += meson.get_compiler('c').find_library('rts2800_fpu32_eabi.lib', dirs: [my_lib_path])
# link_deps = declare_dependency(link_with: my_lib, include_directories: project_inc)
my_lib = []
my_lib += 'C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib/rts2800_fpu32_eabi.lib'
my_lib += 'C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib/libc.a'
my_lib += meson.current_source_dir() + '/platform/ti_c2000_tms320f280039c/src/lsl/28003x_generic_flash_lnk.cmd'
src_dir = meson.current_source_dir()
message('Current src dir:' + src_dir)
# link_deps = declare_dependency(link_args: ['C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/lib/libc.a'], include_directories: project_inc)
link_deps = declare_dependency(link_args: [my_lib], include_directories: project_inc)
# link_deps = dependency()
# link_deps += dependency('rts2800_fpu32_eabi.lib')

# compile the main executable
main = executable('ti_c2000',
  project_src,
  name_suffix : 'out',
  c_args : c_args,
  link_args : [c_link_args],
  dependencies : link_deps,
  include_directories : [project_inc])
