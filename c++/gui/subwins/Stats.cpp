#include <sstream>
#include <iomanip>
#include "gui/subwins/Stats.hpp"
#include "gui/utils/Magic.hpp"

using namespace Chip8::GUI::Subwin;

Stats::Stats(const Chip8::Interpreter::StackInfo& stack)
    : ASubwin(Chip8::GUI::Magic::Windows::Sizes::Stats,
              Chip8::GUI::Magic::Windows::Pos::Stats,
              Chip8::GUI::Magic::Windows::Names::Stats),
      stack_(stack)
{
    // Init Instruction;
    disp_[Insn].setPosition(Chip8::GUI::Magic::Windows::Pos::StatsInsn);
    disp_[Insn].setFillColor(Chip8::GUI::Magic::Colors::Text);
    disp_[Insn].setCharacterSize(Chip8::GUI::Magic::Fonts::DefaultSize + 5);
    // Init Stack;
    disp_[Stack].setPosition(Chip8::GUI::Magic::Windows::Pos::StatsStack);
    disp_[Stack].setFillColor(Chip8::GUI::Magic::Colors::Text);
    disp_[Stack].setCharacterSize(Chip8::GUI::Magic::Fonts::DefaultSize + 3);

    // TMP
    updateInstruction(0, 0xAAA);
    updateStack();
}

void Stats::setFont(const sf::Font& f) noexcept
{
    name_.setFont(f);
    for (auto& disp : disp_)
        disp.setFont(f);
}

static void setHexa(std::ostringstream& oss)
{
    oss << std::setbase(16) << std::uppercase;
}

void Stats::updateInstruction(const Opcode cur, const Addr pc) noexcept
{
    std::ostringstream oss;

    setHexa(oss);
    oss << "Instruction:\t0x" << cur << std::endl;
    oss << "PC:\t\t\t 0x" << pc;
    disp_[Insn].setString(oss.str());
}

void Stats::updateStack() noexcept
{
    std::ostringstream oss;

    setHexa(oss);
    for (int i = 0; const auto stack : stack_.getStack())
        oss << "s" << i++ << ": 0x" << stack << std::endl;
    oss << "SP: 0x" << stack_.getSP();
    disp_[Stack].setString(oss.str());
}

const Stats::Displays& Stats::getDisplays() const noexcept
{
    return disp_;
}

sf::RenderWindow& Chip8::GUI::Subwin::operator<<(sf::RenderWindow& win, const Stats& sub)
{
    win.draw(sub.getWin());
    const auto& name = sub.getName();
    win.draw(name.getRect());
    win.draw(name.getText());
    for (const auto& disp : sub.getDisplays())
        win.draw(disp);
    return win;
}
