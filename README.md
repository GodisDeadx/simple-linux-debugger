simple linux debugger

simple linux debugger is a minimalistic debugger implemented in C++. It leverages the ptrace system call to trace and control the execution of a target process. The debugger provides basic functionality like setting breakpoints, stepping through code, and examining register values.
Features

    Breakpoints: Set breakpoints at specific addresses, file lines, or function names.
    Stepping: Step into, over, or out of functions during execution.
    Backtrace: Print a function call backtrace.
    Variable Inspection: Read and print variables during program execution.
    Memory Access: Read from and write to memory at specified addresses.
    Symbol Lookup: Look up symbols by name.

Building and Running
Prerequisites

    C++ compiler with C++14 support
    Linux operating system (tested on Debian)

Dependencies

simple linux debugger relies on the following external libraries:

    libelfin: A lightweight library for handling ELF (Executable and Linkable Format) files.
    linenoise-ng: A readline replacement library that provides a simple command-line interface.

Build

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

Run

    $ ./dbg <executable_to_debug>

Usage

Once the debugger is running, you can interact with it using a command-line interface. Some of the available commands include:

    cont: Continue execution
    break [ADDRESS|FILE:LINE|FUNCTION]: Set a breakpoint
    step: Step into the next instruction
    next: Step over the next line
    finish: Finish executing the current function
    register dump: Dump register values
    memory read ADDRESS: Read memory at the specified address
    memory write ADDRESS VALUE: Write a value to the specified address
    symbol NAME: Lookup symbol by name
    stepi: Step a single instruction with breakpoint check
    backtrace: Print function call backtrace
    variables: Read and print variables
    exit: Exit the debugger
    clear: Clear the screen
    help: Display the list of available commands

License

This project is licensed under the GNU General Public License v3.0 - see the LICENSE file for details.
Acknowledgments
