#ifndef C8_COMMON_HPP
#define C8_COMMON_HPP

namespace Chip8::Common {

    using v2i = struct{int x, y;};
    using Byte = uint8_t;
    using Addr = uint16_t;
    using Opcode = uint16_t;
}

#endif /* C8_COMMON_HPP */
