#include "Chip8.hpp"

Chip8::Chip8::Chip8()
    : interp_(),
      gui_(interp_)
{}

void Chip8::Chip8::run()
{
    while (gui_.isOpen()) {
        if (gui_.handleEvents())
            return;
        gui_.draw();
    }
}
