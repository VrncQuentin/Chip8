#ifndef C8_INTERP_TIMER_HPP
#define C8_INTERP_TIMER_HPP

#include "Types.hpp"

namespace Chip8::Interp {

    class Timer {
    public:
        static constexpr auto freq = 60;
    public:
        Timer() = default;
        ~Timer() = default;

    public:
        void run() noexcept;

    public:
        void set(byte time) noexcept;
        byte get() const noexcept;

    private:
        byte t_;
    };
}

#endif /* C8_INTERP_TIMER_HPP */