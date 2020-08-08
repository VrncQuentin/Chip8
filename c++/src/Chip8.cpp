#include "Chip8.hpp"

// using namespace Chip8;

void Chip8::Chip8::run()
{
    while (gui_.isOpen()) {
        if (gui_.handleEvents())
            return;
        gui_.draw();
    }
}
