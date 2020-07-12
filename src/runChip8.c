#include "interpreter.h"
#include "instructions.h"

USE_MAJORS_TAB;

int runChip8(struct Chip8 *c)
{
    uint8_t *prog = c->memory.beginProg;

    dumpChip8(c);
    do {
        uint16_t op = prog[c->pc] << 8 | prog[c->pc + 1];
        if (op <= 0)
            break;
        c->pc += 2;
        uint16_t major = MAJOR_IDX(op);
        if (major >= MAJORS)
            exitBadInstruction(op);
        MAJORS_FN[major](c, op);
    } while (c->pc < c->memory.progSize);
    return 0;
}
