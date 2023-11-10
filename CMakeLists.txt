cmake_minimum_required(VERSION 3.10)
project(debugger CXX)

# Run pkg-config to get compiler flags and linker flags
execute_process(COMMAND pkg-config --cflags --libs libdwarf++ OUTPUT_VARIABLE PKG_CONFIG_RESULT OUTPUT_STRIP_TRAILING_WHITESPACE)

# Split result into a list
string(REPLACE " " ";" PKG_CONFIG_LIST ${PKG_CONFIG_RESULT})

# Add source files to the project
add_executable(app main.cpp)

# Add the pkg-config flags to the compile and link options
target_include_directories(app PRIVATE /usr/local/lib)
target_include_directories(app PRIVATE ./include/)
target_compile_options(app PRIVATE ${PKG_CONFIG_LIST})
target_link_options(app PRIVATE ${PKG_CONFIG_LIST})

# Link libs
target_link_libraries(app PRIVATE linenoise)
target_link_libraries(app PRIVATE dwarf++)
target_link_libraries(app PRIVATE elf++)

# cmake_minimum_required(VERSION 3.10)
# project(debugger CXX)

# # Find Libdwarf++ using pkg-config
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBDWARFXX REQUIRED libdwarf++)

# # Add source files to the project
# add_executable(app main.cpp)

# # Include directories and compile options from pkg-config
# target_include_directories(app PRIVATE ${LIBDWARFXX_INCLUDE_DIRS})
# target_compile_options(app PRIVATE ${LIBDWARFXX_CFLAGS_OTHER})

# # Link options and libraries from pkg-config
# target_link_options(app PRIVATE ${LIBDWARFXX_LDFLAGS_OTHER})
# target_link_libraries(app PRIVATE ${LIBDWARFXX_LIBRARIES})

# # Additional link libraries
# target_link_libraries(app PRIVATE linenoise)

