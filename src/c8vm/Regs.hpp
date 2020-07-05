#ifndef C8_VM_REGS_HPP
#define C8_VM_REGS_HPP

/* LibC & STL */
#include <array>

/* Project */
namespace Chip8::VM {

    struct Regs {
    public: /* Useful Types */
        using Data = uint8_t;
        using Addr = uint16_t;
        using Names = enum {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, vA, vB, vC, vD, vE, vF, Max};

    // private: /* Members */
        std::array<Data, Max> data_;
        Addr addr_;
    };
}

#endif /* C8_VM_REGS_HPP */
