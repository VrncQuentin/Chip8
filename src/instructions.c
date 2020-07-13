#include "interpreter.h"
#include "instructions.h"



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

void display(struct Chip8 *c, uint16_t op)
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
