#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interpreter.h"
#include "instructions.h"

#define LI(op, ...)                                         \
    do {                                                    \
        printf("\e[1m%s\e[0m<%04X>:\t", __func__ + 3, op);  \
        printf(__VA_ARGS__);                                \
        printf("\n");                                       \
    } while (0)

void insn_x0(struct Chip8 *c, uint16_t op)
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

void c8_jump(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = INNN(op);

    LI(op, "<OLD: %04x> <PC: %04x>", c->pc, addr);
    c->pc = addr;
}

void c8_call(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = INNN(op);

    LI(op, "<SP: %d> <saved(OLD): %04x> <PC: %04x>", c->stack.sp, c->pc, addr);
    c->stack.stack[c->stack.sp++] = c->pc;
    c->pc = addr;
}

void c8_isEqXNN(struct Chip8 *c, uint16_t op)
{
    uint8_t regData = c->regs.data[IRX(op)];
    uint8_t data = INN(op);

    LI(op, "<reg(%x): %02x> == <data: %02x>", IRX(op), regData, data);
    if (regData == data)
        c->pc += 2;
}

void c8_isDiffXNN(struct Chip8 *c, uint16_t op)
{
    uint8_t regData = c->regs.data[IRX(op)];
    uint8_t data = INN(op);

    LI(op, "<reg(%x): %02x> != <data: %02x>", IRX(op), regData, data);
    if (regData != data)
        c->pc += 2;
}

void c8_isEqXY(struct Chip8 *c, uint16_t op)
{
    uint8_t regX = c->regs.data[IRX(op)];
    uint8_t regY = c->regs.data[IRY(op)];

    LI(op, "<reg(%x): %02x> == <reg(%x): %02x>", IRX(op), regX, IRY(op), regY);
    if (regX == regY)
        c->pc += 2;
}

void c8_set(struct Chip8 *c, uint16_t op)
{
    uint8_t reg = IRX(op);
    uint8_t val = INN(op);

    LI(op, "<%d: %02x>", reg, val);
    c->regs.data[reg] = val;
}

void c8_addXNN(struct Chip8 *c, uint16_t op)
{
    uint8_t reg = IRX(op);
    uint8_t val = INN(op);

    LI(op, "<%d: %02x>", reg, val);
    c->regs.data[reg] += val;
}

void insn_x8(struct Chip8 *c, uint16_t op)
{
    LI(op, "%c", 0);
    (void)c;
}

void c8_isDiffXY(struct Chip8 *c, uint16_t op)
{
    uint8_t regX = c->regs.data[IRX(op)];
    uint8_t regY = c->regs.data[IRY(op)];

    LI(op, "<reg(%x): %02x> != <reg(%x): %02x>", IRX(op), regX, IRY(op), regY);
    if (regX != regY)
        c->pc += 2;
}

void insn_xA(struct Chip8 *c, uint16_t op)
{
    LI(op, "%c", 0);
    (void)c;
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

void c8_display(struct Chip8 *c, uint16_t op)
{
    uint8_t startX = c->regs.data[IRX(op)] % SCR_WIDTH;
    uint8_t startY = c->regs.data[IRY(op)] % SCR_HEIGHT;
    uint8_t size = IN(op);

    LI(op, "<Y: %02x> <X: %02x> <size: %u>", startY, startX, size);
    c->regs.data[vF] = 0;
    for (uint8_t y = 0; y != size && startY + y != SCR_HEIGHT; y += 1) {
        uint8_t row = c->memory.beginProg[c->regs.addr + y];
        for (uint8_t x = 0; x != 8 && startX + x != SCR_WIDTH; x += 1) {
            uint8_t pix = (row >> (7 - x)) & 1;
            if (!pix)
                continue;
            if (c->screen[startY + y][startX + x]) {
                c->screen[startX + y][startX + x] = 0;
                c->regs.data[vF] = 1;
            } else {
                c->screen[startX + y][startX + x] = 1;
            }
        }
    }
    drawScreen(c->screen);
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
