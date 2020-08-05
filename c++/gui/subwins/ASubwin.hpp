#ifndef C8_GUI_SUBWIN_HPP
#define C8_GUI_SUBWIN_HPP

#include <SFML/Graphics.hpp>
#include "GUI.hpp"
#include "utils/Rect.hpp"
// #include "utils/Text.hpp"

namespace Chip8::GUI::Subwin {

    class ASubwin {
    public:
        explicit ASubwin(const Chip8::GUI::Rect::Info& ri) : rect_(ri) {}
        ~ASubwin() = default;

    public:
        const Chip8::GUI::Rect& getRect() const noexcept {return rect_;}

    private:
        Chip8::GUI::Rect rect_;
    };

    // class ASubwin {

    // public:
    //     ASubwin& setText(Chip8::GUI::Text txt, const std::string &name) noexcept
    //         {
    //             txt_ = txt;
    //             setTextString(name);
    //             return *this;
    //         }

    //     ASubwin& setTextString(const std::string &msg) noexcept
    //         {
    //             txt_.setString(msg);
    //             return *this;
    //         }

    //     ASubwin& setTextPosition(float x, float y) noexcept
    //         {
    //             txt_.setPosition(x, y);
    //             return *this;
    //         }

    // public:
    //     const sf::Text& getText() const noexcept {return txt_.getText();}

    // private:
    //     Chip8::GUI::Text txt_;
    // };
}

#endif /* C8_GUI_SUBWIN_HPP */
