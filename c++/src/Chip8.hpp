#ifndef C8_HPP
#define C8_HPP

#include "gui/GUI.hpp"

namespace Chip8 {

    class Chip8 {
    public:
        Chip8() = default;
        ~Chip8() = default;

    public:
        void run();

    private:
        GUI::GUI gui_;
    };
}

#endif /* C8_HPP */
