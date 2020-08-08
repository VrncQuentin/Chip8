#ifndef C8_GUI_GAME_HPP
#define C8_GUI_GAME_HPP

#include "gui/subwins/ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Game : public ASubwin
    {
    public:
        Game() : ASubwin(Chip8::GUI::Magic::Windows::Sizes::Game,
                         Chip8::GUI::Magic::Windows::Pos::Game,
                         Chip8::GUI::Magic::Windows::Names::Game)
            {}
        ~Game() = default;
    };
}

#endif /* C8_GUI_GAME_HPP */
