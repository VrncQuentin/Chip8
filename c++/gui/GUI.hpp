#ifndef C8_GUI_HPP
#define C8_GUI_HPP

// STL
#include <string>
// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// Mine
#include "common/Common.hpp"
#include "gui/utils/Magic.hpp"
#include "gui/subwins/Game.hpp"
#include "gui/subwins/Menu.hpp"
#include "gui/subwins/Stats.hpp"

namespace Chip8::GUI {

    class GUI {
    public:
        const sf::Vector2f Size = Chip8::GUI::Magic::Windows::Sizes::GUI;

    public:
        GUI();
        ~GUI();

    public:
        void draw();
        [[nodiscard]] bool handleEvents() noexcept;

    public:
        [[nodiscard]] bool isOpen() const noexcept;

    private:
        sf::RenderWindow win_;
        sf::Font font_;
        Subwin::Game game_;
        Subwin::Menu menu_;
        Subwin::Stats stats_;
        sf::Event ev_;
        bool drawFlag;
    };
}
#endif /* C8_GUI_HPP */
