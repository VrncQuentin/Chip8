#ifndef C8_GUI_MENU_HPP
#define C8_GUI_MENU_HPP

#include "ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Menu : public ASubwin
    {
    public:
        static constexpr Chip8::GUI::Rect::Info ri = {
            Chip8::GUI::Magic::Windows::Sizes::Menu,
            Chip8::GUI::Magic::Windows::Pos::Menu,
        };

    public:
        Menu() : ASubwin(ri) {}
        ~Menu() = default;
    };
}

#endif /* C8_GUI_MENU_HPP */
