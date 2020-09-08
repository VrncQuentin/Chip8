#ifndef C8_INTERP_REGS_HPP
#define C8_INTERP_REGS_HPP

#include "Types.hpp"
#include "Timers.hpp"

namespace Chip8::Interp {

    class Memory;
    class Regs {
    public:
        using name = enum {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, vA, vB, vC, vD, vE, vF, vMax};
    public:
        Regs() = default;
        ~Regs() = default;

    public:
        void setData(byte value, uint16_t reg) noexcept;
        void addData(byte value, uint16_t reg) noexcept;
        void setAddr(addr value) noexcept;

        void clearCarry() noexcept;
        void setCarry() noexcept;
        void setCarry(bool value) noexcept;

        [[nodiscard]] byte getDataAt(uint16_t reg) const noexcept;
        [[nodiscard]] addr getAddr() const noexcept;

        void setDelayTimer(byte time) noexcept;
        void setSoundTimer(byte time) noexcept;
        [[nodiscard]] const Timer& getDelayTimer() const noexcept;
        [[nodiscard]] const Timer& getSoundTimer() const noexcept;

    private:
        byte data_[vMax]{};
        addr addr_{};
        Timer delay_;
        Timer sound_;
    };
}

#endif /* C8_INTERP_REGS_HPP */
