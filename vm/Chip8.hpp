#ifndef C8_VM_HPP
#define C8_VM_HPP

#include <cstdint>
#include <array>

#include "Regs.hpp"

namespace Chip8 {
    using byte = uint8_t;
    using pixel = uint8_t;
    using opcode = uint16_t;

    class VM {
    public: /* Specs */
        static constexpr uint16_t memory_size = 4096;
        static constexpr uint16_t load_addr = 512;

        static constexpr uint8_t video_width = 64;
        static constexpr uint8_t video_height = 32;

        using videoMemory = std::array<pixel, video_width * video_height>;
        using vmMemory = std::array<byte, memory_size>;

    public:
        VM();
    public:
        void dump_screen() const;
        void dump_memory() const;

    private: /* Members */
        videoMemory screen_;
        vmMemory mem_;
        Regs regs_;
        uint16_t pc_;
    };
};



#endif /* C8_VM_HPP */
