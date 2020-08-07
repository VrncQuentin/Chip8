#ifndef C8_GUI_HPP
#define C8_GUI_HPP

// STL
#include <string>
// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// Mine
#include "Common.hpp"
#include "utils/Magic.hpp"
#include "subwins/ASubwin.hpp"

namespace Chip8::GUI {

    class GUI {
    public:
        const sf::Vector2f Size = Chip8::GUI::Magic::Windows::Sizes::GUI;

    public:
        GUI();
        ~GUI();

    public:
        void run();
        void draw();
        [[nodiscard]] bool handleEvents() noexcept;

    public:
        [[nodiscard]] bool isOpen() const noexcept;

    private:
        sf::RenderWindow win_;
        sf::Font font_;
        std::array<Subwin::ASubwin, Chip8::GUI::Magic::Windows::SubwinCount> subs_;
        sf::Event ev_;
    };
}
#endif /* C8_GUI_HPP */
