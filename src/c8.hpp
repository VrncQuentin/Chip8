#ifndef C8_HPP
#define C8_HPP

namespace Chip8 {

    using opcode = uint16_t;

    struct Specs {
        static constexpr uint16_t memory_size = 4096;
        static constexpr uint16_t load_addr = 512;
    };
}

#endif /* C8_HPP */
