#include "interpreter.h"
#include "instructions.h"


static uint16_t fetch(const uint8_t *prog, const uint16_t pc)
{
    return prog[pc] << 8 | prog[pc + 1];
}

static opfn decode(const uint16_t op)
{
    uint16_t major = MAJOR_IDX(op);
    USE_MAJORS_TAB;

    if (major >= MAJORS)
        return NULL;
    return MAJORS_TAB[major];
}

int runChip8(struct Chip8 *c)
{
    uint8_t *prog = c->memory.beginProg;
    uint16_t op;
    opfn execute;

    while ((op = fetch(prog, c->pc))) {
        c->pc += 2;
        if (!(execute = decode(op)))
            continue;
        execute(c, op);
    };
    return 0;
}
