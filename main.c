#include <stdio.h>
#include "interpreter.h"

int main(int ac, char **av)
{
    if (ac != 2) return 1;
    struct Chip8 interp = {0};

    if (initChip8(&interp, av[1])) {
        fprintf(stderr, "c8i: invalid file\n");
        return 1;
    }
    return runChip8(&interp);
}
