#ifndef C8_GUI_STATS_HPP
#define C8_GUI_STATS_HPP

#include "subwins/ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Stats : public ASubwin
    {
    public:
        static constexpr Chip8::GUI::Rect::Info ri = {
            Chip8::GUI::Magic::Windows::Sizes::Stats,
            Chip8::GUI::Magic::Windows::Pos::Stats,
        };

    public:
        Stats() : ASubwin(ri, Chip8::GUI::Magic::Windows::Names::Stats) {}
        ~Stats() = default;
    };
}

#endif /* C8_GUI_STATS_HPP */
