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
    switch (INN(op)) {
    case ICLEAR:
        c8_clear(c->screen);
    case IRETURN:
        c8_return(&c->stack, &c->pc);
    default:
        exitBadInstruction(op);
    }
}

void c8_jump(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = INNN(op);

    LI("(op: %04x) <OLD: %04x> <PC: %04x>", op, c->pc, addr);
    c->pc = addr;
}

void c8_call(struct Chip8 *c, uint16_t op)
{
    uint16_t addr = INNN(op);

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
    uint8_t reg = IRX(op);
    uint8_t val = INN(op);

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

void c8_display(struct Chip8 *c, uint16_t op)
{
    uint8_t startX = c->regs.data[IRX(op)] % SCR_WIDTH;
    uint8_t startY = c->regs.data[IRY(op)] % SCR_HEIGHT;
    uint8_t size = IN(op);

    LI("(op: %04x) <Y: %02x> <X: %02x> <size: %u>", op, startY, startX, size);
    dumpRegs(&c->regs);
    c->regs.data[vF] = 0;
    for (uint8_t y = 0; y != size && startY + y != SCR_HEIGHT; y += 1) {
        uint8_t row = c->memory.beginProg[c->regs.addr + y];
        for (uint8_t x = 0; x != sizeof(x) && startX + x != SCR_WIDTH; x += 1) {
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
    puts(__func__);
}

void insn_xF(struct Chip8 *c, uint16_t op)
{
    puts(__func__);
}
