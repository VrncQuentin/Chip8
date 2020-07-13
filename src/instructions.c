#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"
#include "instructions.h"

#define LI(...)                                 \
    do {                                        \
        printf("\e[1m%s\e[0m: ", __func__);    \
        printf(__VA_ARGS__);                    \
        printf("\n");                           \
    } while (0)

#define case  break; case
#define default break; default

static void c8_clear(uint8_t screen[SCR_HEIGHT][SCR_WIDTH])
{
    clearScreen(screen);
    LI("done");
}

static void c8_return(struct Stack *s, uint16_t *pc)
{
    if (s->sp == 0) {
        LI("returning from main subroutine, bye o/");
        exit(0);
    }
    uint16_t addr = s->stack[--s->sp];

    LI("<SP: %d> <OLD: %04x> <poped(PC): %04x>", s->sp, *pc, addr);
    *pc = addr;
}

void insn_x0(struct Chip8 *c, uint16_t op)
{
    // 0xNNN is ignored because we don't run on legacy hardware and wont/cant
    // execute subroutines written in machine lang of these computers
    switch (op & 0x00FF) {
    case 0x00E0:
        c8_clear(c->screen);
    case 0x00EE:
        c8_return(&c->stack, &c->pc);
    default:
        exitBadInstruction(op);
    }
}

void c8_jump(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = op & 0x0FFF;

    LI("(op: %04x) <OLD: %04x> <PC: %04x>", op, c->pc, addr);
    c->pc = addr;
}

void c8_call(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = op & 0x0FFF;

    LI("(op: %04x) <SP: %d> <saved(OLD): %04x> <PC: %04x>",
       op, c->stack.sp, c->pc, addr);
    c->stack.stack[c->stack.sp++] = c->pc;
    c->pc = addr;
}

void insn_x3(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_x4(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_x5(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void c8_set(struct Chip8 *c, uint16_t op)
{
    uint8_t reg = (op & 0x0F00) >> 8;
    uint8_t val = op & 0x00FF;

    LI("(op: %04x) <%d: %02x>", op, reg, val);
    c->regs.data[reg] = val;
}

void insn_x7(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_x8(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_x9(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_xA(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_xB(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_xC(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_xD(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_xE(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_xF(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}
