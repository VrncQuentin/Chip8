#include <iostream>
#include "GUI.hpp"
#include "utils/Magic.hpp"

using namespace Chip8::GUI;

GUI::GUI()
    : win_(sf::VideoMode(Size.x, Size.y), Magic::Windows::Names::Main)
{}

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
    win_ << game_ << menu_ << stats_;
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

sf::RenderWindow& Chip8::GUI::operator<<(sf::RenderWindow &win, Subwin::ASubwin& sub)
{
    win.draw(sub.getRect());
    return win;
}
