# Project Conventions

## What is this project?
It is a demo LED blinking project using the CMake build tool for learning.

Key features listed below:
1. Can be built with CMake
2. Can be built with TI Code Composer Studio (CCS)
3. With FreeRTOS operating system

## How to build the project?

### Build with CCS
Just import it as a CCS project and build the `Debug` option.

### Build with CMake
1. Set the toolchain path of in the `\platform\<toolchain>\build_cmake.bat`
2. Click `build.bat` in the project root folder

## Folder Structure
See also [Folder Structure Conventions](https://github.com/kriasoft/Folder-Structure-Conventions)

```
.
├── .git                                # git repository
├── .gitignore                          # git ignored files configuration
├── .clang-format                       # C language formatter cofiguration
├── build                               # Compiled files (alternatively `dist`)
├── docs                                # Documentation files (alternatively `doc`)
├── platform                            # Hardware related
│   └── xxx_mcu                         # MCU hardware
│       ├── script                      # Device assistance scripts
│       ├── src                         # MCU hardware related source
│       ├── toolchain_for_cmake.cmake   # Toolchain CMake configuration
│       └── build_cmake.bat             # Toolchain related build command
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
├── build.bat                           # Batch command that invokes CMake
├── LICENSE                             # See https://choosealicense.com/
└── README.md
```

## C Language Naming Conventions
Consider a source file as a module.
Becase C language does not have the namespace.

So objects with pubic visibility should have a file name prefix like
`file_name_`.
While objects with private visibility should have a `_` prefix to indicate the
operation scope.

Summary table showed below:

| Object            | Convention                                | Example                                    |
| -                 | -                                         | -                                          |
| file              | snake_case                                | `demo_file.c`, `demo_file.h`               |
| global macro      | file_name_UPPER_CASE                      | `demo_file_MACRO_A`                        |
| global struct     | file_name_PascalCase                      | `demo_file_StructOne`                      |
| global enum       | file_name_PascalCase                      | `demo_file_EnumerateOne`                   |
| global enum value | file_name_PascalCase                      | `demo_file_EnumerateOne_Value1`            |
| global variable   | file_name_snake_case                      | `demo_file_global_var`                     |
| global function   | file_name_function_name                   | `demo_file_do_something()`                 |
| local macro       | UPPER_CASE                                | `MACRO_A`                                  |
| local struct      | PascalCase                                | `SomeStruct`                               |
| local enum        | PascalCase                                | `SomeEnum`                                 |
| local enum value  | PascalCase                                | `SomeEnum_ValOne`                          |
| local variable    | s_snake_case                              | `s_static_var`                             |
| local function    | s_snake_case                              | `s_do_something()`                         |
| temp variable     | snake_case                                | `temp_var`                                 |
| param in          | snake_case                                | `param`                                    |
| param out         | o_snake_case                              | `o_param`                                  |
| param in and out  | io_snake_case                             | `io_param`                                 |
| hex               | lower case                                | `0xab`                                     |
| comment           | First character upper case, javadoc style | `/** Comment */`, `/**< Inline comment */` |
