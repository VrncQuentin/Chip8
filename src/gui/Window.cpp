#include "gui/Window.hpp"

using namespace Chip8::GUI;

Window::Window()
    : sf::RenderWindow(sf::VideoMode(800, 600), "Chip8::Interpreter")
{
    if (!font_.loadFromFile("static/SCP-Regular.ttf"))
        throw std::exception();
}

Window::~Window() {
    close();
}

const sf::Font &Window::getFont() const noexcept {
    return font_;
}
