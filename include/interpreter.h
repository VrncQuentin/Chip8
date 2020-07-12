#ifndef C8_INTERPRETER_H
#define C8_INTERPRETER_H

#include <stdint.h>
#include <stddef.h>

enum InfoChip8 {
    MEMORY_SIZE = 4096,
    LOAD_ADDR = 512,
    STACKS_NB = 16,

};

enum IOChip8 {
    FREQ_DELAY = 60,
    FREQ_SOUND = 60,

    SCR_WIDTH = 64,
    SCR_HEIGHT = 32,
    SCR_SIZE = SCR_WIDTH * SCR_HEIGHT,

    FONT_BYTES = 5,
    FONT_COUNT = 16,
};

#define USE_FONTS_TAB                                        \
    static const uint8_t FONTS[FONT_COUNT][FONT_BYTES] = {   \
        {0xF0, 0x90, 0x90, 0x90, 0xF0},                      \
        {0x20, 0x60, 0x20, 0x20, 0x70},                      \
        {0xF0, 0x10, 0xF0, 0x80, 0xF0},                      \
        {0xF0, 0x10, 0xF0, 0x10, 0xF0},                      \
        {0x90, 0x90, 0xF0, 0x10, 0x10},                      \
        {0xF0, 0x80, 0xF0, 0x10, 0xF0},                      \
        {0xF0, 0x80, 0xF0, 0x90, 0xF0},                      \
        {0xF0, 0x10, 0x20, 0x40, 0x40},                      \
        {0xF0, 0x90, 0xF0, 0x90, 0xF0},                      \
        {0xF0, 0x90, 0xF0, 0x10, 0xF0},                      \
        {0xF0, 0x90, 0xF0, 0x90, 0x90},                      \
        {0xE0, 0x90, 0xE0, 0x90, 0xE0},                      \
        {0xF0, 0x80, 0x80, 0x80, 0xF0},                      \
        {0xE0, 0x90, 0x90, 0x90, 0xE0},                      \
        {0xF0, 0x80, 0xF0, 0x80, 0xF0},                      \
        {0xF0, 0x80, 0xF0, 0x80, 0x80}                       \
    }

struct RAM {
    uint8_t buf[MEMORY_SIZE];
    uint8_t *beginProg;
    size_t progSize;
    uint8_t *fonts;
};

enum regsName {
    v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, vA, vB, vC, vD, vE, vF, vMax
};

struct Regs {
    uint8_t data[vMax];
    uint16_t addr;
};

struct Timers {
    uint8_t delay;
    uint8_t sound;
};

struct Stack {
    uint16_t stack[STACKS_NB];
    uint16_t sp;
};

struct Chip8 {
    struct RAM memory;
    struct Regs regs;
    struct Stack stack;
    struct Timers timers;
    uint16_t pc;
    uint8_t screen[SCR_HEIGHT][SCR_WIDTH];
};

int initChip8(struct Chip8 *c, char const *fp);
int runChip8(struct Chip8 *c);
void dumpChip8(const struct Chip8 *c);

void clearScreen(uint8_t screen[SCR_HEIGHT][SCR_WIDTH]);
void drawScreen(const uint8_t screen[SCR_HEIGHT][SCR_WIDTH]);

#endif /* C8_INTERPRETER_H */
