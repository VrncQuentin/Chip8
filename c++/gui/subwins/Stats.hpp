#ifndef C8_GUI_STATS_HPP
#define C8_GUI_STATS_HPP

#include "common/Common.hpp"
#include "gui/subwins/ASubwin.hpp"

using namespace Chip8::Common;

namespace Chip8::GUI::Subwin {

    class Stats : public ASubwin
    {
        // using InfoIdx = enum {Insn, Regs, Stack, Timers, Max};
        // using Info = std::array<sf::Text, Max>;
    public:
        static constexpr int winLeftPad = 5;
    public:
        Stats();
        ~Stats() = default;

    public:
        Stats& setFont(const sf::Font& f) noexcept;
        Stats& setInstruction(const Opcode cur, const Addr pc) noexcept;
        // Stats& setRegs(const Chip8::Common::Byte cur, int idx) noexcept;

    public:
        const sf::Text& getInstruction() const noexcept;

    private:
        // Info info_;
        sf::Text insn_; /* Current Instruction + PC*/
        // sf::Text regs_; /* v0 - vF + vI */
        // Chip8::Interpreter::Regs regsRef;
        // sf::Text stack_; /* s0 - sF + SP */
        // sf::Text timers_; /* Delay + Sound */
    };
    sf::RenderWindow& operator<<(sf::RenderWindow& win, const Stats& sub);
}

#endif /* C8_GUI_STATS_HPP */
