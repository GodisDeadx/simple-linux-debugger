#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include <utility>
#include <string>
#include <linux/types.h>
#include <unordered_map>
#include <fcntl.h>
#include <signal.h>

#include "breakpoint.hpp"
#include "./libelfin/dwarf/dwarf++.hh"
#include "./libelfin/elf/elf++.hh"

namespace dbg {

    enum class symbol_type {
        notype,            // No type (e.g., absolute symbol)
        object,            // Data object
        func,              // Function entry point
        section,           // Symbol is associated with a section
        file,              // Source file associated with the
    };                     // object file

    std::string to_string (symbol_type st) {
        switch (st) {
        case symbol_type::notype: return "notype";
        case symbol_type::object: return "object";
        case symbol_type::func: return "func";
        case symbol_type::section: return "section";
        case symbol_type::file: return "file";
        }
        return "notype";
    }

    struct symbol {
        symbol_type type;
        std::string name;
        std::uintptr_t addr;
    };

    class debugger {
    public:
        debugger (std::string prog_name, pid_t pid)
            : m_prog_name{std::move(prog_name)}, m_pid{pid} {
                auto fd = open(m_prog_name.c_str(), O_RDONLY);
                m_elf = elf::elf{elf::create_mmap_loader(fd)};
                m_dwarf = dwarf::dwarf{dwarf::elf::create_loader(m_elf)};
        }

        void run();
        void set_breakpoint_at_address(std::intptr_t);
        void dump_registers();
        void set_pc(uint64_t);
        void step_over_breakpoint();
        void wait_for_signal();
        void initialise_load_address();
        void print_source(const std::string&, unsigned, unsigned);
        void handle_sigtrap(siginfo_t);
        void single_step_instruction();
        void single_step_instruction_with_breakpoint_check();
        void step_out();
        void remove_breakpoint(std::intptr_t);
        void step_in();
        void step_over();
        void set_breakpoint_at_function(const std::string&);
        void set_breakpoint_at_source_line(const std::string&, unsigned);
        void write_memory(uint64_t, uint64_t);
        void print_backtrace();
        void read_variables();

        uint64_t get_offset_pc();
        uint64_t read_memory(uint64_t);
        uint64_t get_pc();
        uint64_t offset_load_address(uint64_t);
        uint64_t offset_dwarf_address(uint64_t);

        dwarf::die get_function_from_pc(uint64_t);
        dwarf::line_table::iterator get_line_entry_from_pc(uint64_t);

        siginfo_t get_signal_info();

        std::vector<symbol> lookup_symbol(const std::string&);

    private:
        void handle_command(const std::string& line);
        void continue_execution();        

        std::string m_prog_name;
        pid_t m_pid;
        std::unordered_map<std::intptr_t,breakpoint> m_breakpoints;
        uint64_t m_load_address = 0;

        dwarf::dwarf m_dwarf;
        elf::elf m_elf;

    };
};
#endif