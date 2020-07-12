#include <string.h>
#include <stdio.h>
#include "interpreter.h"
#include "instructions.h"

void insn_x0(struct Chip8 *c, uint16_t op)
{
    // 0xNNN is ignored because we don't run on legacy hardware and wont/cant
    // execute subroutines written in machine lang of these computers
    puts(__func__);
    switch (op & 0x00FF) {
    case 0x00E0:
        clearScreen(c->screen);
        puts("clear screen");
        break;
    case 0x00EE:
        puts("return");
        break;
    default:
        exitBadInstruction(op);
    }
}

void insn_x1(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}

void insn_x2(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
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

void insn_x6(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
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
