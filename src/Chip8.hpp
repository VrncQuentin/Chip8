#ifndef C8_CHIP8_HPP
#define C8_CHIP8_HPP

#include <string>
#include "interpreter/Memory.hpp"
#include "interpreter/Regs.hpp"
#include "interpreter/Stack.hpp"
#include "gui/Window.hpp"
#include "gui/Screen.hpp"

namespace Chip8 {

    class Chip8 {
    public:
        Chip8() = default;
        ~Chip8() = default;

    public:
        [[nodiscard]] bool loadNewGame(const std::string& gamePath) noexcept;
        int run() noexcept;
        void draw() noexcept;

    private:
        static constexpr auto decodeMajor = [](const uint16_t op)
                {return static_cast<uint16_t>((op & 0xF000) >> 12);};

        static constexpr auto decodeRegX = [](const uint16_t op)
                {return static_cast<uint16_t>((op & 0x0F00) >> 8);};

        static constexpr auto decodeRegY = [](const uint16_t op)
                {return static_cast<uint16_t>((op & 0x00F0) >> 4);};

        static constexpr auto decodeN = [](const uint16_t op)
                {return  static_cast<uint16_t>(op & 0x000F);};

        static constexpr auto decodeNN = [](const uint16_t op)
                {return  static_cast<uint16_t>(op & 0x00FF);};

        static constexpr auto decodeNNN = [](const uint16_t op)
                {return  static_cast<uint16_t>(op & 0x0FFF);};

        void exec(const uint16_t op) noexcept;


    private:
        Interp::Memory ram_;
        Interp::Regs regs_;
        Interp::Stack stack_{};
        GUI::Window win_;
        GUI::Screen scr_;
    };
}

#endif /* C8_CHIP8_HPP */
