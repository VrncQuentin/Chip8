#ifndef C8_INTERP_CONST_HPP
#define C8_INTERP_CONST_HPP

#include "Types.hpp"

namespace Chip8::Interp {

    static constexpr unsigned int MemorySize = 4096;
    static constexpr addr LoadAddr = 0x200;
    static constexpr unsigned int MaxProgSize = MemorySize - LoadAddr;
}

#endif /* C8_INTERP_CONST_HPP */
