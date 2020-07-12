#ifndef C8_INTERP_INSTRUCTIONS_H
#define C8_INTERP_INSTRUCTIONS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define MAJOR_IDX(op) ((op & 0xF000) / 0x1000)
#define MAJORS        (MAJOR_IDX(0xF000) + 1)

struct Chip8;
typedef void (*opfn)(struct Chip8 *c, uint16_t op);

void insn_x0(struct Chip8 *c, uint16_t op);
void insn_x1(struct Chip8 *c, uint16_t op);
void insn_x2(struct Chip8 *c, uint16_t op);
void insn_x3(struct Chip8 *c, uint16_t op);
void insn_x4(struct Chip8 *c, uint16_t op);
void insn_x5(struct Chip8 *c, uint16_t op);
void insn_x6(struct Chip8 *c, uint16_t op);
void insn_x7(struct Chip8 *c, uint16_t op);
void insn_x8(struct Chip8 *c, uint16_t op);
void insn_x9(struct Chip8 *c, uint16_t op);
void insn_xA(struct Chip8 *c, uint16_t op);
void insn_xB(struct Chip8 *c, uint16_t op);
void insn_xC(struct Chip8 *c, uint16_t op);
void insn_xD(struct Chip8 *c, uint16_t op);
void insn_xE(struct Chip8 *c, uint16_t op);
void insn_xF(struct Chip8 *c, uint16_t op);

#define USE_MAJORS_TAB                          \
    static const opfn MAJORS_FN[MAJORS] = {     \
        insn_x0,                                \
        insn_x1,                                \
        insn_x2,                                \
        insn_x3,                                \
        insn_x4,                                \
        insn_x5,                                \
        insn_x6,                                \
        insn_x7,                                \
        insn_x8,                                \
        insn_x9,                                \
        insn_xA,                                \
        insn_xB,                                \
        insn_xC,                                \
        insn_xD,                                \
        insn_xE,                                \
        insn_xF                                 \
    }

__attribute__((noreturn, always_inline))
static inline void exitBadInstruction(uint16_t op)
{
    fprintf(stderr, "unsupported opcode 0x%04x\n", op);
    exit(2);
}


#endif /* C8_INTERP_INSTRUCTIONS_H */
