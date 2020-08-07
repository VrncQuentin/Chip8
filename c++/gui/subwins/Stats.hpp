#ifndef C8_GUI_STATS_HPP
#define C8_GUI_STATS_HPP

#include "subwins/ASubwin.hpp"

namespace Chip8::GUI::Subwin {

    class Stats : public ASubwin
    {
    public:
        Stats() : ASubwin(Chip8::GUI::Magic::Windows::Sizes::Stats,
                          Chip8::GUI::Magic::Windows::Pos::Stats,
                          Chip8::GUI::Magic::Windows::Names::Stats)
            {}
        ~Stats() = default;
    };
}

#endif /* C8_GUI_STATS_HPP */
