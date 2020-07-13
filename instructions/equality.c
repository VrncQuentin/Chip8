#include "interpreter.h"
#include "instructions.h"

void xnnSkipEqual(struct Chip8 *c, uint16_t op)
{
    uint8_t regData = c->regs.data[IRX(op)];
    uint8_t data = INN(op);

    LI(op, "<reg(%x): %02x> == <data: %02x>", IRX(op), regData, data);
    if (regData == data)
        c->pc += 2;
}

void xnnSkipDiff(struct Chip8 *c, uint16_t op)
{
    uint8_t regData = c->regs.data[IRX(op)];
    uint8_t data = INN(op);

    LI(op, "<reg(%x): %02x> != <data: %02x>", IRX(op), regData, data);
    if (regData != data)
        c->pc += 2;
}

void xySkipEqual(struct Chip8 *c, uint16_t op)
{
    uint8_t regX = c->regs.data[IRX(op)];
    uint8_t regY = c->regs.data[IRY(op)];

    LI(op, "<reg(%x): %02x> == <reg(%x): %02x>", IRX(op), regX, IRY(op), regY);
    if (regX == regY)
        c->pc += 2;
}

void xySkipDiff(struct Chip8 *c, uint16_t op)
{
    uint8_t regX = c->regs.data[IRX(op)];
    uint8_t regY = c->regs.data[IRY(op)];

    LI(op, "<reg(%x): %02x> != <reg(%x): %02x>", IRX(op), regX, IRY(op), regY);
    if (regX != regY)
        c->pc += 2;
}
