#ifndef C8_INTERP_INSTRUCTIONS_H
#define C8_INTERP_INSTRUCTIONS_H

#include <stdint.h>

/* Majors tell us what kind of instructions we're dealing with */
#define MAJOR_IDX(op) ((op & 0xF000) >> 12)
#define MAJORS        (MAJOR_IDX(0xF000) + 1)

/* Instruction nibbles give us informations to handle the major */
#define IRX(op) ((op & 0x0F00) >> 8)
#define IRY(op) ((op & 0x00F0) >> 4)
#define IN(op)   (op & 0x000F)
#define INN(op)  (op & 0x00FF)
#define INNN(op) (op & 0x0FFF)

enum nibbles {
    ICLEAR = 0x00E0,
    IRETURN = 0x00EE
};

struct Chip8;
typedef void (*opfn)(struct Chip8 *c, uint16_t op);

/* Flow */
void jump(struct Chip8 *c, uint16_t op);
void jumpWithOffset(struct Chip8 *c, uint16_t op);
void call(struct Chip8 *c, uint16_t op);
//void _return(struct Chip8 *c, uint16_t op);

/* Equality */
void xnnSkipEqual(struct Chip8 *c, uint16_t op);
void xnnSkipDiff(struct Chip8 *c, uint16_t op);
void xySkipEqual(struct Chip8 *c, uint16_t op);
void xySkipDiff(struct Chip8 *c, uint16_t op);

/* Math & Logic */
void xnnSet(struct Chip8 *c, uint16_t op); /* Sets data reg(X) with NN */
void innnSet(struct Chip8 *c, uint16_t op); /* Sets addr reg(i) with NNN */
void xnnAdd(struct Chip8 *c, uint16_t op);
void doLogicAndMathOP(struct Chip8 *c, uint16_t op);
void randomC8(struct Chip8 *c, uint16_t op);

/* Graphical */
//void clear(struct Chip8 *c, uint16_t op);
void display(struct Chip8 *c, uint16_t op);

/* Misc */
void clear_or_return(struct Chip8 *c, uint16_t op);

void insn_xE(struct Chip8 *c, uint16_t op);
void insn_xF(struct Chip8 *c, uint16_t op);

#define USE_MAJORS_TAB                          \
    static const opfn MAJORS_TAB[MAJORS] = {    \
        /* Inconditional */                     \
        [0x1] = jump,                           \
        [0xB] = jumpWithOffset,                 \
        [0x2] = call,                           \
        /* Conditional */                       \
        [0x3] = xnnSkipEqual,                   \
        [0x4] = xnnSkipDiff,                    \
        [0x5] = xySkipEqual,                    \
        [0x9] = xySkipDiff,                     \
        /* Math & Logic */                      \
        [0xA] = innnSet,                        \
        [0x6] = xnnSet,                         \
        [0x7] = xnnAdd,                         \
        [0x8] = doLogicAndMathOP,               \
        [0xC] = randomC8,                       \
        /* Graphical */                         \
        [0xD] = display,                        \
        /* Misc */                              \
        [0x0] = clear_or_return,                \
        [0xE] = insn_xE,                        \
        [0xF] = insn_xF                         \
    }

#include <stdio.h>
#define LI(op, ...)                                     \
    do {                                                \
        printf("%s<\e[1m%04X\e[0m>:\t", __func__, op);  \
        printf(__VA_ARGS__);                            \
        printf("\n");                                   \
    } while (0)


#endif /* C8_INTERP_INSTRUCTIONS_H */
