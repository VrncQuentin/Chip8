#ifndef C8_GUI_MENU_HPP
#define C8_GUI_MENU_HPP

#include "ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Menu : public ASubwin
    {
    public:
        Menu() : ASubwin(Chip8::GUI::Magic::Windows::Sizes::Menu,
                         Chip8::GUI::Magic::Windows::Pos::Menu,
                         Chip8::GUI::Magic::Windows::Names::Menu)
            {}
        ~Menu() = default;
    };
}

#endif /* C8_GUI_MENU_HPP */
