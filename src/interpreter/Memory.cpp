#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "interpreter/Memory.hpp"

using namespace Chip8::Interp;

static constexpr Chip8::byte fonts[5 * 16] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0,
        0x20, 0x60, 0x20, 0x20, 0x70,
        0xF0, 0x10, 0xF0, 0x80, 0xF0,
        0xF0, 0x10, 0xF0, 0x10, 0xF0,
        0x90, 0x90, 0xF0, 0x10, 0x10,
        0xF0, 0x80, 0xF0, 0x10, 0xF0,
        0xF0, 0x80, 0xF0, 0x90, 0xF0,
        0xF0, 0x10, 0x20, 0x40, 0x40,
        0xF0, 0x90, 0xF0, 0x90, 0xF0,
        0xF0, 0x90, 0xF0, 0x10, 0xF0,
        0xF0, 0x90, 0xF0, 0x90, 0x90,
        0xE0, 0x90, 0xE0, 0x90, 0xE0,
        0xF0, 0x80, 0x80, 0x80, 0xF0,
        0xE0, 0x90, 0x90, 0x90, 0xE0,
        0xF0, 0x80, 0xF0, 0x80, 0xF0,
        0xF0, 0x80, 0xF0, 0x80, 0x80
};

Memory::Memory() : buf_(), pc_(LoadAddr)
{
    reset();
}

void Memory::loadFonts() noexcept {
    memcpy(buf_, fonts, sizeof(fonts));
}

bool Memory::loadGame(const std::string &path) noexcept {
    int fd = open(path.c_str(), O_RDONLY);
    if (fd == -1)
        return false;

    struct stat st{};
    fstat(fd, &st);
    if (st.st_size >= MaxProgSize)
        return false;
    reset();
    return read(fd, buf_ + LoadAddr, static_cast<size_t>(st.st_size)) != -1;
}

void Memory::reset() noexcept {
    bzero(buf_, MemorySize);
    loadFonts();
}

uint16_t Memory::fetch() noexcept {
    const auto op = static_cast<const uint16_t>(buf_[pc_] << 8 | buf_[pc_ + 1]);
    incrementPC();
    return op;
}

void Memory::setPC(const Chip8::addr jumpTo) noexcept {
    pc_ = jumpTo;
}

Chip8::addr Memory::getPC() const noexcept {
    return pc_;
}

void Memory::incrementPC() noexcept {
    pc_ += 2;
}

Chip8::byte Memory::operator[](const Chip8::addr idx) const noexcept {
    if (idx >= MemorySize)
        return 0;
    return buf_[idx];
}

void Memory::show() noexcept {
    for (int i = 0; i != MemorySize; i += 1) {
        printf("0x%X ", buf_[i]);
        if (!(i % 32))
            puts("");
    }
}

void Memory::putInMem(Chip8::addr where, Chip8::byte what) noexcept {
    buf_[where] = what;
}

void Memory::decrementPC() noexcept {
    pc_ -= 2;
}

Chip8::byte Memory::getFromMem(Chip8::addr where) const noexcept {
    return buf_[where];
}
