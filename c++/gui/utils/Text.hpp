#ifndef C8_GUI_TEXT_HPP
#define C8_GUI_TEXT_HPP

#include <SFML/Graphics.hpp>
#include "utils/Magic.hpp"
#include "utils/Exception.hpp"

namespace Chip8::GUI {

    class Text {
    public:
        Text() = default;
        Text(const std::string& fontPath)
            {
                if (!f_.loadFromFile(fontPath))
                    throw Errors::Font("Failed to load font" + fontPath);
                t_.setFont(f_);
                t_.setFillColor(Chip8::GUI::Magic::NameFontColor);
                t_.setCharacterSize(10);
            }
        ~Text() = default;

    public:
        void setString(const std::string& s)
            {
                t_.setString(s);
            }

        void setPosition(float x, float y) noexcept
            {
                t_.setPosition(sf::Vector2f(x, y));
            }

    public:
        const sf::Text& getText() const noexcept {return t_;}

    private:
        sf::Font f_;
        sf::Text t_;
    };
}

#endif /* C8_GUI_TEXT_HPP */
