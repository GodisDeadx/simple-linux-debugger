cmake_minimum_required(VERSION 3.10)
project(debugger CXX)

# add_compile_options(-std=c++14)

# Run pkg-config to get compiler flags and linker flags
execute_process(COMMAND pkg-config --cflags --libs libdwarf++ OUTPUT_VARIABLE PKG_CONFIG_RESULT OUTPUT_STRIP_TRAILING_WHITESPACE)

# Split result into a list
string(REPLACE " " ";" PKG_CONFIG_LIST ${PKG_CONFIG_RESULT})

# Add source files to the project
add_executable(dbg main.cpp)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -gdwarf-4")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -gdwarf-4")

add_executable(break tests/break.cpp)
set_target_properties(break
                      PROPERTIES COMPILE_FLAGS "-g -O0 -gdwarf-4")
add_executable(steps tests/steps.cpp)
set_target_properties(steps
                      PROPERTIES COMPILE_FLAGS "-g -O0 -gdwarf-4")

# Add the pkg-config flags to the compile and link options
target_include_directories(dbg PRIVATE /usr/local/lib)
target_include_directories(dbg PRIVATE ./include/)
target_compile_options(dbg PRIVATE ${PKG_CONFIG_LIST})
target_link_options(dbg PRIVATE ${PKG_CONFIG_LIST})

# Link libs
target_link_libraries(dbg PRIVATE linenoise)
target_link_libraries(dbg PRIVATE dwarf++)
target_link_libraries(dbg PRIVATE elf++)
