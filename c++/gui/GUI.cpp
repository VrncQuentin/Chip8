// STL
#include <iostream>
// Mine
#include "GUI.hpp"
#include "subwins/Game.hpp"
#include "subwins/Menu.hpp"
#include "subwins/Stats.hpp"
#include "utils/Exception.hpp"

using namespace Chip8::GUI;

GUI::GUI()
    : win_(sf::VideoMode(Size.x, Size.y), Magic::Windows::Names::Main),
      subs_{Subwin::Game(), Subwin::Stats(), Subwin::Menu()}
{
    if (!font_.loadFromFile(Magic::Fonts::DefaultPath))
        throw Errors::Font("failed to load font from " + std::string(Magic::Fonts::DefaultPath));
    for (auto& sub : subs_)
        sub.setFont(font_);
}

GUI::~GUI()
{
    win_.close();
}

void GUI::run()
{
    while (isOpen()) {
        if (handleEvents())
            return;
        draw();
    }
}

void GUI::draw()
{
    win_.clear(Magic::Colors::Filler);
    for (const auto& sub : subs_)
        win_ << sub;
    win_.display();
}

bool GUI::handleEvents() noexcept
{
    while (win_.pollEvent(ev_))
        if (ev_.type == sf::Event::Closed)
            return true;
    return false;
}

bool GUI::isOpen() const noexcept
{
    return win_.isOpen();
}

sf::RenderWindow& Chip8::GUI::operator<<(sf::RenderWindow &win, const Subwin::ASubwin& sub)
{
    win.draw(sub.getRect());
    win.draw(sub.getName());
    return win;
}
