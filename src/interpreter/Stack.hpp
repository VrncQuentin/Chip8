#ifndef C8_INTERP_STACK_HPP
#define C8_INTERP_STACK_HPP

#include "Types.hpp"

namespace Chip8::Interp {

    class Stack {
    public:
        static constexpr auto size = 0x10;
    public:
        Stack() = default;
        ~Stack() = default;

    public:
        void push(const addr value) noexcept;
        [[nodiscard]] addr pop() noexcept;

    private:
        addr buf_[0x10];
        addr sp_;
    };
}

#endif /* C8_INTERP_STACK_HPP */