#ifndef C8_INTERP_REGS_HPP
#define C8_INTERP_REGS_HPP

#include "Types.hpp"

namespace Chip8::Interp {

    class Memory;
    class Regs {
    public:
        using name = enum {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, vA, vB, vC, vD, vE, vF, vMax};
    public:
        Regs() = default;
        ~Regs() = default;

    public:
        void setData(const byte value, const uint16_t reg) noexcept;
        void clearCarry() noexcept;
        void setCarry() noexcept;
        void setCarry(bool value) noexcept;
        void addData(const byte value, const uint16_t reg) noexcept;
        void setAddr(const addr value) noexcept;

        [[nodiscard]] byte getDataAt(const uint16_t reg) const noexcept;
        [[nodiscard]] addr getAddr() const noexcept;

    private:
        byte data_[vMax]{};
        addr addr_{};
    };
}

#endif /* C8_INTERP_REGS_HPP */
