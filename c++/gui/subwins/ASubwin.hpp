#ifndef C8_GUI_SUBWIN_HPP
#define C8_GUI_SUBWIN_HPP

#include <SFML/Graphics.hpp>
#include "GUI.hpp"
#include "utils/Rect.hpp"
// #include "utils/Text.hpp"

namespace Chip8::GUI::Subwin {

    class ASubwin {
    public:
        explicit ASubwin(const Chip8::GUI::Rect::Info& ri, const std::string& name)
            : rect_(ri)
            {
                name_.setString(name);
                name_.setCharacterSize(Chip8::GUI::Magic::Fonts::DefaultSize);
                name_.setFillColor(Chip8::GUI::Magic::Colors::Text);
            }
        ~ASubwin() = default;

    public:
        void setFont(const sf::Font& f) noexcept {name_.setFont(f);}

    public:
        const Chip8::GUI::Rect& getRect() const noexcept {return rect_;}
        const sf::Text& getName() const noexcept {return name_;}

    private:
        Chip8::GUI::Rect rect_;
        sf::Text name_;
    };
}

#endif /* C8_GUI_SUBWIN_HPP */
