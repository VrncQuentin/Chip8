#include "interpreter.h"
#include "instructions.h"

void innnSet(struct Chip8 *c, uint16_t op)
{
    LI(op, "<addr(old): %03x> <addr(new): %03x>", c->regs.addr, INNN(op));
    c->regs.addr = INNN(op);
}

void insn_xB(struct Chip8 *c, uint16_t op)
{
    LI(op, "%c", 0);
    (void)c;
}

void insn_xC(struct Chip8 *c, uint16_t op)
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
