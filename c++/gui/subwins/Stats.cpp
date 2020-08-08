#include <sstream>
#include <iomanip>
#include "gui/subwins/Stats.hpp"
#include "gui/utils/Magic.hpp"

using namespace Chip8::GUI::Subwin;

Stats::Stats()
    : ASubwin(Chip8::GUI::Magic::Windows::Sizes::Stats,
              Chip8::GUI::Magic::Windows::Pos::Stats,
              Chip8::GUI::Magic::Windows::Names::Stats)
{
    const auto& win = getPosition();
    const auto yPos = win.y + winLeftPad;
    const sf::Vector2f posInsn(win.x + 10, yPos);
    // const sf::Vector2f posInsn(win.x + 30, yPos);

    // Init Instruction;
    insn_.setPosition(posInsn);
    insn_.setFillColor(Chip8::GUI::Magic::Colors::Text);
    insn_.setCharacterSize(Chip8::GUI::Magic::Fonts::DefaultSize + 5);
    // Init Regs;
    // regs_.setPosition(pos);
    // regs_.setFillColor(Chip8::GUI::Magic::Colors::Text);
    // regs_.setCharacterSize(Chip8::GUI::Magic::Fonts::DefaultSize + 3);
    // TMP
    setInstruction(0, 0);
    // for (int x = 0; x != 0x10; x++)
    //     setRegs(x, 0);

}

Stats& Stats::setFont(const sf::Font& f) noexcept
{
    name_.setFont(f);
    insn_.setFont(f);
    return *this;
}

Stats& Stats::setInstruction(const Opcode cur, const Addr pc) noexcept
{
    std::ostringstream oss;

    oss << "Instruction:\t0x" << std::setbase(16) << cur << std::endl;
    oss << "PC:\t\t\t 0x" << std::setbase(16) << pc;
    insn_.setString(oss.str());
    return *this;
}

// Stats& Stats::setRegs(const Chip8::Common::Byte cur, int idx) noexcept
// {
    
// }

const sf::Text& Stats::getInstruction() const noexcept
{
    return insn_;
}

sf::RenderWindow& Chip8::GUI::Subwin::operator<<(sf::RenderWindow& win, const Stats& sub)
{
    win.draw(sub.getWin());
    const auto& name = sub.getName();
    win.draw(name.getRect());
    win.draw(name.getText());
    win.draw(sub.getInstruction());
    return win;
}
