# TI C2000 CMake Meson

## Introduction
It is a demo LED blinking project using the CMake / Meson build tool for learning.<br>
Run on the **Texas Instrument C2000 F280039C launch pad**.

Key features listed below:
1. With CMake build tool support
2. With Meson build tool support
3. With TI Code Composer Studio (CCS) build support
4. Using FreeRTOS realtime operating system

## How to build the project?
### Prerequisites
- [TI Code Composer Studio (CCS)](https://www.ti.com/tool/CCSTUDIO)
- [CMake](https://cmake.org/download/)
- [Meson](https://github.com/mesonbuild/meson/releases)
- [Ninja](https://github.com/ninja-build/ninja/releases)

### Build with CCS
Just import it as a CCS project and build the `Debug` option.

### Build with CMake
1. Set your toolchain path `ccs_dir` in the `\platform\<toolchain>\build_cmake.bat`
2. Uncomment the `set buildtool=cmake` in the `build.bat` file
3. Click `build.bat` in the project root folder

### Build with Meson
1. Set your toolchain path `ccs_dir` in the `\platform\<toolchain>\build_meson.bat`
2. Uncomment the `set buildtool=meson` in the `build.bat` file
3. Click `build.bat` in the project root folder

## Folder Structure
See also [Folder Structure Conventions](https://github.com/kriasoft/Folder-Structure-Conventions)

```
.
├── .git                                # git repository
├── .gitignore                          # git ignored files configuration
├── .clang-format                       # C language formatter cofiguration
├── build                               # Compiled files (alternatively `dist`)
│   ├── cmake                           # CMake built files
│   └── meson                           # Meson built files
├── docs                                # Documentation files (alternatively `doc`)
├── platform                            # Hardware related
│   └── xxx_mcu                         # MCU hardware
│       ├── script                      # Device assistance scripts
│       ├── src                         # MCU hardware related source
│       ├── toolchain_for_cmake.cmake   # Toolchain CMake configuration
│       ├── build_cmake.bat             # Toolchain related build command
│       └── build_meson.bat             # Toolchain related build command
├── src                                 # Source files (alternatively `lib` or `app`)
│   ├── asw                             # Application software
│   ├── bsw                             # Basic software
│   │   ├── os                          # Operating system (such as FreeRTOS)
│   │   │   └── freertos                # FreeRTOS operating system
│   │   ├── mcu                         # MCU api interface
│   │   └── drv                         # Driver operations that required multiple MCU api combination
│   └── main.c, .h                      # Main entrance
├── test                                # Automated tests (alternatively `spec` or `tests`)
├── script                              # Project assistance scripts
├── tools                               # Tools and utilities
├── CMakeLists.txt                      # CMake build configuration
├── meson.build                         # Meson build configuration
├── build.bat                           # Batch command that invokes CMake Meson
├── LICENSE                             # See https://choosealicense.com/
└── README.md
```

## C Language Naming Conventions
Consider a source file as a module.<br>
Becase C language does not have the namespace.

So objects with pubic visibility should have a file name prefix like
`file_name_`.<br>
While objects with private visibility should have a `_` prefix to indicate the
operation scope.

Summary table showed below:

| Object                  | Convention                                | Example                                                                                     |
| -                       | -                                         | -                                                                                           |
| file                    | snake_case                                | `demo_file.c`, `demo_file.h`                                                                |
| global macro            | file_name_UPPER_CASE                      | `demo_file_MACRO_A`                                                                         |
| global struct           | file_name_PascalCase                      | `demo_file_StructOne`                                                                       |
| global enum             | file_name_PascalCase                      | `demo_file_EnumerateOne`                                                                    |
| global enum value       | file_name_PascalCase                      | `demo_file_EnumerateOne_Value1`                                                             |
| global variable         | file_name_snake_case                      | `demo_file_global_var`                                                                      |
| global function         | file_name_function_name                   | `demo_file_do_something()`                                                                  |
| local macro             | UPPER_CASE                                | `MACRO_A`                                                                                   |
| local struct            | PascalCase                                | `SomeStruct`                                                                                |
| local enum              | PascalCase                                | `SomeEnum`                                                                                  |
| local enum value        | PascalCase_PascalCase                     | `SomeEnum_ValOne`                                                                           |
| local variable          | s_snake_case                              | `s_static_var`                                                                              |
| local function          | f_snake_case()                            | `f_do_something()`                                                                          |
| interface input vars    | IF_I_UPPER_CASE                           | `IF_I_MACRO_A`                                                                              |
| interface output vars   | IF_O_UPPER_CASE                           | `IF_O_MACRO_A`                                                                              |
| interface in / out vars | IF_IO_UPPER_CASE                          | `IF_IO_MACRO_A`                                                                             |
| interface function      | IF_F_UPPER_CASE                           | `IF_F_MACRO_A`                                                                              |
| interface type          | IF_T_UPPER_CASE                           | `IF_T_MACRO_A`                                                                              |
| temp variable           | snake_case                                | `temp_var`                                                                                  |
| param in                | snake_case                                | `param`                                                                                     |
| param out               | o_snake_case                              | `o_param`                                                                                   |
| param in and out        | io_snake_case                             | `io_param`                                                                                  |
| hex                     | lower case                                | `0xab`                                                                                      |
| normal comment          | First character upper case                | `// Inine comment`<br><br>`// Line comment`<br><br>`//`<br>`// Block comment`<br>`//`       |
| doxygen comment         | First character upper case, doxygen style | `///< Inine comment`<br><br>`/// Line comment`<br><br>`///`<br>`/// Block comment`<br>`///` |
