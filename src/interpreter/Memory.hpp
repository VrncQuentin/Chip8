#ifndef C8_INTERP_MEMORY_HPP
#define C8_INTERP_MEMORY_HPP

#include "Types.hpp"
#include "interpreter/Const.hpp"

namespace Chip8::Interp {

    class Memory {
    public:
        Memory();
        ~Memory() = default;

    public:
        [[nodiscard]] bool loadGame(const std::string& path) noexcept;
        void reset() noexcept;

    public:
        [[nodiscard]] uint16_t fetch() noexcept;
        [[nodiscard]] addr getPC() const noexcept;
        void setPC(addr jumpTo) noexcept;
        void incrementPC() noexcept;
        void show() noexcept;

    public:
        byte operator[](const addr idx) const noexcept;

    private:
        void loadFonts() noexcept;

    private:
        byte buf_[Interp::MemorySize];
        addr pc_{};
    };
}

#endif /* C8_INTERP_MEMORY_HPP */