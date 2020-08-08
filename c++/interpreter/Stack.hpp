#ifndef C8_INTERP_STACK_HPP
#define C8_INTERP_STACK_HPP

#include <array>
#include "common/Common.hpp"

namespace Chip8::Interpreter {

    class StackInfo {
    public:
        static constexpr int Max = 0x10;
        using Stack = std::array<Chip8::Common::Addr, Max>;

    public:
        StackInfo() = default;
        ~StackInfo() = default;

    public:
        void push(const Chip8::Common::Addr addr) noexcept
            {
                s_[sp_++] = addr;
            }

        [[nodiscard]] Chip8::Common::Addr pop() noexcept
            {
                return s_[--sp_];
            }

    public:
        [[nodiscard]] const Stack& getStack() const noexcept {return s_;}
        [[nodiscard]] Chip8::Common::Addr getSP() const noexcept {return sp_;}

    private:
        Stack s_;
        Chip8::Common::Addr sp_;
    };
}

#endif /* C8_INTERP_STACK_HPP */
