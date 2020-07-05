#ifndef C8_VM_HPP
#define C8_VM_HPP

/* LibC && STL */
#include <string>
#include <array>
#include <iostream>


namespace Chip8 {
    /* Useful types */

    class VM {
    public: /* Registers*/
        using Regs = struct vmRegs {
            using data = uint8_t;
            using addr = uint16_t;

            std::array<data, 16> data_;
            addr addr_;
        };

    public: /* Graphical */
        using Screen = struct vmScreen {
        };

    public: /* Memory */
        using vmMemory = std::array<byte, Specs::memory_size>;

    public:
        void dump_screen() const {scr_.dumpScreen()}
        void dump_memory() const;

    private: /* Members */
        Screen scr_;
        vmMemory memBuf_{0};
        Regs regs_;
        uint16_t pc_;
    };
};



#endif /* C8_VM_HPP */
