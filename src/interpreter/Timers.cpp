#include "Timers.hpp"

void Chip8::Interp::Timer::run() noexcept {

}

void Chip8::Interp::Timer::set(Chip8::byte time) noexcept {
    t_ = time;
}

Chip8::byte Chip8::Interp::Timer::get() const noexcept {
    return t_;
}
