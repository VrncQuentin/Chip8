#ifndef C8_GUI_RECT_HPP
#define C8_GUI_RECT_HPP

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include "Common.hpp"
#include "utils/Magic.hpp"

namespace Chip8::GUI {

    class Rect : public sf::RectangleShape
    {
    public:
        enum InfoIdx {riSize, riPos, riMax};
        using Info = Chip8::Common::v2i[riMax];

    public:
        explicit Rect(const Info& ri, bool useDefaults = true)
            : sf::RectangleShape(sf::Vector2f(ri[riSize].x, ri[riSize].y))
            {
                setPosition(sf::Vector2f(ri[riPos].x, ri[riPos].y));
                if (useDefaults)
                    setBorder();
            }
        ~Rect() = default;

    public:
        Rect& setBorder(
            sf::Color inner = Chip8::GUI::Magic::Colors::Filler,
            sf::Color border = Chip8::GUI::Magic::Colors::Border,
            float size = Chip8::GUI::Magic::Windows::Sizes::Borders) noexcept
            {
                setFillColor(inner);
                setOutlineColor(border);
                setOutlineThickness(size);
                return *this;
            };
    };
}

#endif /* C8_GUI_UTILS_RECT_HPP */
