#include "interpreter.h"
#include "instructions.h"

USE_MAJORS_TAB;

static uint16_t getNextInstr(const uint8_t *prog, const uint16_t pc)
{
    return prog[pc] << 8 | prog[pc + 1];;
}

int runChip8(struct Chip8 *c)
{
    uint8_t *prog = c->memory.beginProg;
    uint16_t op;

    while ((op = getNextInstr(prog, c->pc))) {
        c->pc += 2;
        uint16_t major = MAJOR_IDX(op);
        if (major >= MAJORS)
            continue;
        MAJORS_TAB[major](c, op);
    };
    return 0;
}
