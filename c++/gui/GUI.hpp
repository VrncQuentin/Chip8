#ifndef C8_GUI_HPP
#define C8_GUI_HPP

// STL
#include <string>
// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// Mine
#include "Common.hpp"
#include "subwins/Game.hpp"
#include "subwins/Menu.hpp"
#include "subwins/Stats.hpp"

namespace Chip8::GUI {

    class GUI {
    public:
        static constexpr Chip8::Common::v2i Size = Chip8::GUI::Magic::Windows::Sizes::GUI;

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
        sf::Event ev_;
        // std::array<Subwin::ASubwin, 3> subs_;
        Subwin::Game game_;
        Subwin::Menu menu_;
        Subwin::Stats stats_;
    };

    sf::RenderWindow& operator<<(sf::RenderWindow &win, Subwin::ASubwin& sub);
}

#endif /* C8_GUI_HPP */
