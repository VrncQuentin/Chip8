#include <stdlib.h>
#include "interpreter.h"
#include "instructions.h"

void clear_or_return(struct Chip8 *c, uint16_t op)
{
    // 0xNNN is ignored because we don't run on legacy hardware and wont/cant
    // execute subroutines written in machine lang of these computers
    switch (INN(op)) {
    case ICLEAR:
        clearScreen(c->screen);
        LI(op, "clear");
        break;
    case IRETURN:
        if (c->stack.sp == 0) {
            LI(op, "returning from main subroutine, bye o/");
            exit(0);
        }
        uint16_t addr = c->stack.stack[--c->stack.sp];
        LI(op, "<SP: %d> <OLD: %04x> <poped(PC): %04x>", c->stack.sp, c->pc, addr);
        c->pc = addr;
    }
}

void jump(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = INNN(op);

    LI(op, "<OLD: %04x> <PC: %04x>", c->pc, addr);
    c->pc = addr;
}

void call(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = INNN(op);

    LI(op, "<SP: %d> <saved(OLD): %04x> <PC: %04x>", c->stack.sp, c->pc, addr);
    c->stack.stack[c->stack.sp++] = c->pc;
    c->pc = addr;
}
