#ifndef C8_GUI_SCREEN_HPP
#define C8_GUI_SCREEN_HPP

#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Types.hpp"

namespace Chip8::GUI {

    class Screen {
    public:
        static constexpr auto Width = 64;
        static constexpr auto Height = 32;
        static constexpr auto Size = Width * Height;
        static constexpr auto PixelSize = 8;
        const sf::Color& PixON = sf::Color::White;
        const sf::Color& PixOFF = sf::Color::Black;

    public:
        Screen();
        ~Screen() = default;

    public:
        void draw(sf::RenderWindow& win) const noexcept;
        void clear() noexcept;
        bool toggle(const byte x, const byte y) noexcept;

    private:
    sf::RectangleShape scr_[Size];
    };
}

#endif /* C8_GUI_SCREEN_HPP */