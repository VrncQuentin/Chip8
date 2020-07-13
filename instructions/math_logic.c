#include "interpreter.h"
#include "instructions.h"

void xnnSet(struct Chip8 *c, uint16_t op)
{
    uint8_t reg = IRX(op);
    uint8_t val = INN(op);

    LI(op, "<%d: %02x>", reg, val);
    c->regs.data[reg] = val;
}

void xnnAdd(struct Chip8 *c, uint16_t op)
{
    uint8_t reg = IRX(op);
    uint8_t val = INN(op);

    LI(op, "<%d: %02x>", reg, val);
    c->regs.data[reg] += val;
}

void doLogicAndMathOP(struct Chip8 *c, uint16_t op)
{
    uint8_t regX = IRX(op);
    uint8_t regY = IRY(op);
//    uint16_t rv;

    switch (IN(op)) {
    case 0x0: /* Set vX with vY */
    {
        c->regs.data[regX] = c->regs.data[regY];
        break;
    }
    case 0x1: /* Logical OR */
    {        c->regs.data[regX] |= c->regs.data[regY];
        break;
    }
    case 0x2: /* Logical AND */
    {    c->regs.data[regX] &= c->regs.data[regY];
        break;
    }
    case 0x3: /* Logical XOR */
    {
        c->regs.data[regX] ^= c->regs.data[regY];
        break;
    }
    case 0x4: /* vX += vY (sets vF if overflow) */
    {
        uint16_t rv = c->regs.data[regX] + c->regs.data[regY];
        c->regs.data[vF] = rv > __UINT8_MAX__;
        c->regs.data[regX] = rv;
        break;
    }
    case 0x5: /* vX = vX - vY */
    {
        c->regs.data[vF] = c->regs.data[regX] > c->regs.data[regY];
        c->regs.data[regX] = c->regs.data[regX] - c->regs.data[regY];
        break;
    }
    case 0x6: /* vX <<= 1 (sets vF with the shifted-out bit) */
    {
        c->regs.data[vF] = c->regs.data[regX] & (1 << 7);
        c->regs.data[regX] <<= 1;
        break;
    }
    case 0x7: /* vX = vY - vX */
    {
        c->regs.data[vF] = c->regs.data[regY] > c->regs.data[regX];
        c->regs.data[regX] = c->regs.data[regY] - c->regs.data[regX];
        break;
    }
    case 0xE: /* vX >>= 1 (sets vF with the shifted-out bit) */
    {
        c->regs.data[vF] = c->regs.data[regX] & 1;
        c->regs.data[regX] >>= 1;
        break;
    }
    }
}
