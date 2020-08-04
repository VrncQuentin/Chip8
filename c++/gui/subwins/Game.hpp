#ifndef C8_GUI_GAME_HPP
#define C8_GUI_GAME_HPP

#include "subwins/ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Game : public ASubwin
    {
    public:
        static constexpr int Width = 512;
        static constexpr int Height = 256;
        static constexpr Chip8::GUI::Rect::Info ri = {
            Chip8::Common::v2i{Width, Height}, // Size
            Chip8::Common::v2i{10, 10}         // Pos
        };

    public:
        Game() : ASubwin(ri) {}
        ~Game() = default;
    };
}

#endif /* C8_GUI_GAME_HPP */
