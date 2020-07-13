#include <stdio.h>
#include "interpreter.h"

static void dumpRegs(const struct Regs *r)
{
    printf("\e[1m*** Regs\e[0m\n\e[1maddr\e[0m:\t<%d>\n", r->addr);
    printf("\e[1mdata\e[0m:\t<%02x", r->data[v0]);
    for (uint8_t i = v1; i != vMax; i += 1)
        printf(", %02x", r->data[i]);
    printf(">\n\n");
}

static void dumpStack(const struct Stack *s)
{
    printf("\e[1m*** Stack\e[0m\n");
    printf("\e[1msp\e[0m:\t<%d>\n\e[1mctt\e[0m:\t<%02x", s->sp, s->stack[0]);
    for (uint8_t i = 1; i < s->sp; i += 1)
        printf(", %02x", s->stack[i]);
    printf(">\n\n");
}

static const uint16_t line_sz = 16;
static const uint16_t lines = (MEMORY_SIZE - LOAD_ADDR) / line_sz;
static const uint16_t mid = line_sz / 2;

static uint16_t getY(uint16_t y)
{
    return y * line_sz;
}

static uint16_t getPosYX(uint16_t y, uint16_t x)
{
    return getY(y) + x;
}

static void dumpRAM(const struct RAM *r)
{
    printf("\e[1m*** Memory\e[0m: %zu\n", r->progSize);
    for (uint16_t y = 0; y != lines; y += 1) {
        printf("\e[1m%04x\e[0m:\t", getY(y));
        for (uint16_t x = 0; x != line_sz; x += 1) {
            if (getPosYX(y, x) == r->progSize) {
                printf("\n\n");
                return;
            }
            if (x == mid)
                printf(" ");
            printf("%02x ", r->beginProg[getPosYX(y, x)]);
        }
        printf("\n");
    }
}

static void dumpPC(uint16_t pc)
{
    printf("\e[1m*** PC\e[0m: <%d>\n\n", pc);
}

static void dumpTimers(const struct Timers *t)
{
    printf("\e[1m*** Timers\e[0m\n");
    printf("\e[1mdelay\e[0m: <%d>\n", t->delay);
    printf("\e[1msound\e[0m: <%d>\n\n", t->sound);
}

void dumpChip8(const struct Chip8 *c)
{
    printf("\t\e[1m***** Interpreter's State *****\e[0m\n");
    dumpRegs(&c->regs);
    dumpStack(&c->stack);
    dumpPC(c->pc);
    dumpRAM(&c->memory);
    dumpTimers(&c->timers);
    printf("\t\e[1m*******************************\e[0m\n");
}
