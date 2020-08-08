// STL
#include <iostream>
// Mine
#include "GUI.hpp"
#include "utils/Exception.hpp"

using namespace Chip8::GUI;

GUI::GUI()
    : win_(sf::VideoMode(Size.x, Size.y), Magic::Windows::Names::Main)
{
    if (!font_.loadFromFile(Magic::Fonts::DefaultPath))
        throw Errors::Font("failed to load font from " + std::string(Magic::Fonts::DefaultPath));
    game_.setFont(font_);
    menu_.setFont(font_);
    stats_.setFont(font_);
    drawFlag = true;
}

GUI::~GUI()
{
    win_.close();
}

void GUI::draw()
{
    if (!drawFlag)
        return;
    win_.clear(Magic::Colors::Filler);
    win_ << game_ << menu_;
    win_ << stats_;
    win_.display();
    drawFlag = false;
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

