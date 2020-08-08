#ifndef C8_HPP
#define C8_HPP

#include "gui/GUI.hpp"
#include "interpreter/Interpreter.hpp"

namespace Chip8 {

    class Chip8 {
    public:
        Chip8();
        ~Chip8() = default;

    public:
        void run();

    private:
        Interpreter::Interp interp_;
        GUI::GUI gui_;
    };
}

#endif /* C8_HPP */
