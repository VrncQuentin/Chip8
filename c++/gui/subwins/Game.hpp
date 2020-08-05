#ifndef C8_GUI_GAME_HPP
#define C8_GUI_GAME_HPP

#include "subwins/ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Game : public ASubwin
    {
    public:
        static constexpr Chip8::GUI::Rect::Info ri = {
            Chip8::GUI::Magic::Windows::Sizes::Game,
            Chip8::GUI::Magic::Windows::Pos::Game
        };

    public:
        Game() : ASubwin(ri, Chip8::GUI::Magic::Windows::Names::Game) {}
        ~Game() = default;
    };
}

#endif /* C8_GUI_GAME_HPP */
