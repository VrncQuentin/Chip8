#include "interpreter.h"
#include "instructions.h"

void innnSet(struct Chip8 *c, uint16_t op)
{
    LI(op, "<addr(old): %03x> <addr(new): %03x>", c->regs.addr, INNN(op));
    c->regs.addr = INNN(op);
}

void randomC8(struct Chip8 *c, uint16_t op)
{
    int max = INN(op);
    int reg = IRX(op);
    int rnd = rand();

    c->regs.data[reg] = rnd & max;
    LI(op, "<target: %x> <rand: %x> <max: %02x> <res: %02x>", reg, rnd, max, c->regs.data[reg]);
}

void jumpWithOffset(struct Chip8 *c, uint16_t op)
{
    LI(op, "%c", 0);
    (void)c;
}


void insn_xE(struct Chip8 *c, uint16_t op)
{
    LI(op, "%c", 0);
    (void)c;
}

void insn_xF(struct Chip8 *c, uint16_t op)
{
    LI(op, "%c", 0);
    (void)c;
}
