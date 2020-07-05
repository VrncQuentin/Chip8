#include <iostream>
#include "Chip8.hpp"

int main()
{
    Chip8::VM vm;

    vm.dump_screen();
    vm.dump_memory();
}
