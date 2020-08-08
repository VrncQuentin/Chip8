#ifndef C8_GUI_STATS_HPP
#define C8_GUI_STATS_HPP

#include "common/Common.hpp"
#include "gui/subwins/ASubwin.hpp"
#include "interpreter/Stack.hpp"

using namespace Chip8::Common;

namespace Chip8::GUI::Subwin {

    class Stats : public ASubwin
    {
    public:
        using DisplaysIdx = enum {Insn, Regs, Stack, Timers, Max};
        using Displays = std::array<sf::Text, Max>;

    public:
        static constexpr int winLeftPad = 5;
    public:
        Stats(const Chip8::Interpreter::StackInfo& stack);
        ~Stats() = default;

    public:
        void setFont(const sf::Font& f) noexcept;
        void updateInstruction(const Opcode cur, const Addr pc) noexcept;
        void updateStack() noexcept;

    public:
        [[nodiscard]] const Displays& getDisplays() const noexcept;

    private:
        Displays disp_;
        const Chip8::Interpreter::StackInfo& stack_;
    };
    sf::RenderWindow& operator<<(sf::RenderWindow& win, const Stats& sub);
}

#endif /* C8_GUI_STATS_HPP */
