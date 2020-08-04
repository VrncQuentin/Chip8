#ifndef C8_GUI_MENU_HPP
#define C8_GUI_MENU_HPP

#include "ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Menu : public ASubwin
    {
    public:
        static constexpr int gameHeight = Chip8::GUI::Subwin::Game::Height;
        static constexpr int width = Chip8::GUI::Subwin::Game::Width;
        static constexpr Chip8::GUI::Rect::Info ri = {
            Chip8::Common::v2i{width, 600 - gameHeight - 30},
            Chip8::Common::v2i{10, gameHeight + 20}
        };

    public:
        Menu() : ASubwin(ri) {}
        ~Menu() = default;
    };
}

#endif /* C8_GUI_MENU_HPP */
