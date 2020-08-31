#include "interpreter/Stack.hpp"

using namespace Chip8::Interp;

void Stack::push(const addr value) noexcept {
    if (sp_ >= size)
        return; // TODO: Improve this error handling
    buf_[sp_++] = value;
}

Chip8::addr Stack::pop() noexcept {
    if (!sp_)
        return 0; // TODO: Improve this error handling
    return buf_[--sp_];
}
