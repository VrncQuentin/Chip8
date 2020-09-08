#include "Regs.hpp"

using namespace Chip8::Interp;

void Regs::setData(const Chip8::byte value, const uint16_t reg) noexcept {
    data_[reg] = value;
}

void Regs::addData(const Chip8::byte value, const uint16_t reg) noexcept {
    data_[reg] += value;
}

Chip8::byte Regs::getDataAt(const uint16_t reg) const noexcept {
    return data_[reg];
}

void Regs::setAddr(const Chip8::addr value) noexcept
{
    addr_ = value;
}

Chip8::addr Regs::getAddr() const noexcept
{
    return addr_;
}

void Regs::clearCarry() noexcept {
    data_[vF] = 0;
}

void Regs::setCarry() noexcept {
    data_[vF] = 1;
}

void Regs::setCarry(bool value) noexcept {
    data_[vF] = value;
}

void Regs::setDelayTimer(const Chip8::byte time) noexcept {
    delay_.set(time);
}

void Regs::setSoundTimer(const Chip8::byte time) noexcept {
    sound_.set(time);
}

const Timer &Regs::getDelayTimer() const noexcept {
    return delay_;
}

const Timer &Regs::getSoundTimer() const noexcept {
    return sound_;
}
