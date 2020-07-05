#ifndef C8_VM_HPP
#define C8_VM_HPP

/* LibC && STL */
#include <iostream>

/* Project */
#include "Regs.hpp"
#include "Screen.hpp"

namespace Chip8::VM {

    class VM {
    public: /* Specs */
        static constexpr uint16_t MemorySize = 4096;
        static constexpr uint16_t LoadAddr = 512;

    public: /* Useful Types */
        using Memory = std::array<std::byte, MemorySize>;

    private: /* Members */
        static constexpr Memory buf_{std::byte{0}};
        static constexpr Screen scr_{};
        Regs regs_;
        uint16_t pc;

    private: /* Helper Methods */

    public: /* Methods */
        static constexpr auto run = []()
            {
                scr_.dumpScreen();
            };
    };
};



#endif /* C8_VM_HPP */
