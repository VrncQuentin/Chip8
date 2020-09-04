#ifndef C8_CHIP8_HPP
#define C8_CHIP8_HPP

#include <string>
#include <map>
#include "interpreter/Memory.hpp"
#include "interpreter/Regs.hpp"
#include "interpreter/Stack.hpp"
#include "gui/Window.hpp"
#include "gui/Screen.hpp"

namespace Chip8 {

    class Chip8 {
    public:
        Chip8();
        ~Chip8() = default;

    public:
        [[nodiscard]] bool loadNewGame(const std::string& gamePath) noexcept;
        int run() noexcept;
        void draw() noexcept;
        void exec(uint16_t op) noexcept;

    private:
        static constexpr auto decodeMajor = [](const uint16_t op) -> uint16_t {return (op & 0xF000u) >> 12u;};
        static constexpr auto decodeRegX  = [](const uint16_t op) -> uint16_t {return (op & 0x0F00u) >> 8u;};
        static constexpr auto decodeRegY  = [](const uint16_t op) -> uint16_t {return (op & 0x00F0u) >> 4u;};
        static constexpr auto decodeN     = [](const uint16_t op) -> uint16_t {return  op & 0x000Fu;};
        static constexpr auto decodeNN    = [](const uint16_t op) -> uint16_t {return  op & 0x00FFu;};
        static constexpr auto decodeNNN   = [](const uint16_t op) -> uint16_t {return  op & 0x0FFFu;};

    private:
        using instrTable = std::map<uint16_t, void (Chip8::*)(const uint16_t) noexcept>;
        static const instrTable instructions;

        void clear_or_return(uint16_t op) noexcept;
        void jump(uint16_t op) noexcept;
        void call(uint16_t op) noexcept;
        void skipIfRegEqNN(uint16_t op) noexcept;
        void skipIfRegNeqNN(uint16_t op) noexcept;
        void skipIfRegEqReg(uint16_t op) noexcept;
        void skipIfRegNeqReg(uint16_t op) noexcept;
        void setRegWithNN(uint16_t op) noexcept;
        void addNNtoReg(uint16_t op) noexcept;

        void doMathOperations(uint16_t op) noexcept;
        void doMathSet(uint16_t op) noexcept;
        void doMathOr(uint16_t op) noexcept;
        void doMathAnd(uint16_t op) noexcept;
        void doMathXor(uint16_t op) noexcept;
        void doMathAdd(uint16_t op) noexcept;
        void doMathSubXY(uint16_t op) noexcept;
        void doMathSubYX(uint16_t op) noexcept;
        void doMathSHR(uint16_t op) noexcept;
        void doMathSHL(uint16_t op) noexcept;

        void setAddrReg(uint16_t op) noexcept;
        void jumpWithOffset(uint16_t op) noexcept;
        void random(uint16_t op) noexcept;
        void display(uint16_t op) noexcept;
        void skipIfKey(uint16_t op) noexcept;
        void doMiscOperations(uint16_t op) noexcept;

    private:
        Interp::Memory ram_;
        Interp::Regs regs_;
        Interp::Stack stack_{};
        GUI::Window win_;
        GUI::Screen scr_;
    };
}

#endif /* C8_CHIP8_HPP */
