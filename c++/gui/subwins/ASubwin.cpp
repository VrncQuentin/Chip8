#include "gui/subwins/ASubwin.hpp"
#include "gui/utils/Magic.hpp"

using namespace Chip8::GUI::Subwin;

Name::Name(const std::string &name, const sf::Vector2f& winPos) noexcept
    : rect_(sf::Vector2f(name.length() * 7, Chip8::GUI::Magic::Fonts::DefaultSize))
{
    const sf::Vector2f posText(winPos.x + 10, winPos.y - 8);
    text_.setString(name);
    text_.setPosition(posText);
    text_.setFillColor(Chip8::GUI::Magic::Colors::Text);
    text_.setCharacterSize(Chip8::GUI::Magic::Fonts::DefaultSize);

    const sf::Vector2f posRect(winPos.x + 5, winPos.y - 5);
    rect_.setPosition(posRect);
    rect_.setFillColor(Chip8::GUI::Magic::Colors::FillerFull);
}

Name& Name::setFont(const sf::Font& f) noexcept
{
    text_.setFont(f);
    return *this;
}

const sf::RectangleShape& Name::getRect() const noexcept
{
    return rect_;
}

const sf::Text& Name::getText() const noexcept
{
    return text_;
}

ASubwin::ASubwin(const sf::Vector2f& size, const sf::Vector2f& pos, const std::string& name)
    : win_(size),
      pos_(pos),
      name_(name, pos)
{
    win_.setPosition(pos);
    win_.setFillColor(Chip8::GUI::Magic::Colors::Filler);
    win_.setOutlineColor(Chip8::GUI::Magic::Colors::Border);
    win_.setOutlineThickness(Chip8::GUI::Magic::Windows::Sizes::Borders);
}

const sf::RectangleShape& ASubwin::getWin() const noexcept
{
    return win_;
}

const Name& ASubwin::getName() const noexcept
{
    return name_;
}

const sf::Vector2f& ASubwin::getPosition() const noexcept
{
    return pos_;
}

ASubwin& ASubwin::setFont(const sf::Font& f) noexcept
{
    name_.setFont(f);
    return *this;
}


sf::RenderWindow& Chip8::GUI::Subwin::operator<<(sf::RenderWindow &win, const ASubwin& sub)
{
    win.draw(sub.getWin());
    const auto& name = sub.getName();
    win.draw(name.getRect());
    win.draw(name.getText());
    return win;
}
