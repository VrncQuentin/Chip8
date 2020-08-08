#ifndef C8_INTERP_REGS_HPP
#define C8_INTERP_REGS_HPP

#include <array>
#include "Common.hpp"

namespace Chip8::Interpreter {

    class Regs {
    public:
        static constexpr Chip8::Common::Byte vMax = 0x10;
        using Data = std::array<Chip8::Common::Byte, vMax>;

    public:
        Regs();

    public:
        [[nodiscard]] const Data& getDataRegs() const noexcept {return data_;}
        [[nodiscard]] Chip8::Common::Addr getAddrReg() const noexcept {return addr_;}

    private:
        Data data_;
        Chip8::Common::Addr addr_;
    };
}

#endif /* C8_INTERP_REGS_HPP */
