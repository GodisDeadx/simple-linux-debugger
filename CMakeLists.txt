cmake_minimum_required(VERSION 3.10)
project(debugger CXX)

# add_compile_options(-std=c++14)

# Run pkg-config to get compiler flags and linker flags
execute_process(COMMAND pkg-config --cflags --libs libdwarf++ OUTPUT_VARIABLE PKG_CONFIG_RESULT OUTPUT_STRIP_TRAILING_WHITESPACE)

# Split result into a list
string(REPLACE " " ";" PKG_CONFIG_LIST ${PKG_CONFIG_RESULT})

# Add source files to the project
add_executable(app main.cpp)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -gdwarf-4")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -gdwarf-4")

add_executable(break tests/break.cpp)
set_target_properties(break
                      PROPERTIES COMPILE_FLAGS "-g -O0 -gdwarf-4")
add_executable(steps tests/steps.cpp)
set_target_properties(steps
                      PROPERTIES COMPILE_FLAGS "-g -O0 -gdwarf-4")

# Add the pkg-config flags to the compile and link options
target_include_directories(app PRIVATE /usr/local/lib)
target_include_directories(app PRIVATE ./include/)
target_compile_options(app PRIVATE ${PKG_CONFIG_LIST})
target_link_options(app PRIVATE ${PKG_CONFIG_LIST})

# Link libs
target_link_libraries(app PRIVATE linenoise)
target_link_libraries(app PRIVATE dwarf++)
target_link_libraries(app PRIVATE elf++)
