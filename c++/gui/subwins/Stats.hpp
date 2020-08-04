#ifndef C8_GUI_STATS_HPP
#define C8_GUI_STATS_HPP

#include "subwins/ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Stats : public ASubwin
    {
    public:
        static constexpr int gameWidth = Chip8::GUI::Subwin::Game::Width;
        static constexpr Chip8::GUI::Rect::Info ri = {
            Chip8::Common::v2i{800 - gameWidth - 30, 600 - 20},
            Chip8::Common::v2i{gameWidth + 20, 10}
        };

    public:
        Stats() : ASubwin(ri) {}
        ~Stats() = default;
    };
}

#endif /* C8_GUI_STATS_HPP */
