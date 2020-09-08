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

const Window::inputTable Window::azerty = {
        {sf::Keyboard::Num1, Input::One},
        {sf::Keyboard::Num2, Input::Two},
        {sf::Keyboard::Num3, Input::Three},
        {sf::Keyboard::Num4, Input::C},
        {sf::Keyboard::A, Input::Four},
        {sf::Keyboard::Z, Input::Five},
        {sf::Keyboard::E, Input::Six},
        {sf::Keyboard::R, Input::D},
        {sf::Keyboard::Q, Input::Seven},
        {sf::Keyboard::S, Input::Eight},
        {sf::Keyboard::D, Input::Nine},
        {sf::Keyboard::F, Input::E},
        {sf::Keyboard::Z, Input::A},
        {sf::Keyboard::X, Input::Zero},
        {sf::Keyboard::C, Input::B},
        {sf::Keyboard::V, Input::F},
};

Input Window::getInput() noexcept {
    sf::Event ev{};
    while (pollEvent(ev)) {
        if (ev.type != sf::Event::KeyPressed)
            continue;
        const auto which = azerty.find(ev);
        if (which != azerty.end())
            return which->second;
    }
    return None;
}

