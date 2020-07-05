#include <cstdio>
#include "Chip8.hpp"

using namespace Chip8;

VM::VM()
{
    for (pixel &p : screen_)
        p = 0;
    for (byte &b : mem_)
        b = 0;
}

void VM::dump_screen() const
{
    for (const pixel p : screen_)
        printf("%c", p ? '*' : '_');
    puts("");
}

void VM::dump_memory() const
{
    for (const byte b : mem_)
        printf("%d", b);
    puts("");
}
