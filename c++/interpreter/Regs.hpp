#ifndef C8_INTERP_REGS_HPP
#define C8_INTERP_REGS_HPP

#include <array>
#include "Interpreter.hpp"

namespace Chip8::Interpreter {

    class Regs {
    public:
        static constexpr Data vMax = 0x10;
        using Data = std::array<Byte, vMax>;

    public:
        [[nodiscard]] const Data& getDataRegs() const noexcept {return data_;}
        [[nodiscard]] Addr getAddrReg() const noexcept {return addr_;}

    private:
        Data data_;
        Addr addr_;
    };
}

#endif /* C8_INTERP_REGS_HPP */
