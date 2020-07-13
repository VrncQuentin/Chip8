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

void insn_x0(struct Chip8 *c, uint16_t op);
void c8_jump(struct Chip8 *c, uint16_t op);
void c8_call(struct Chip8 *c, uint16_t op);
void c8_isEqXNN(struct Chip8 *c, uint16_t op);
void c8_isDiffXNN(struct Chip8 *c, uint16_t op);
void c8_isEqXY(struct Chip8 *c, uint16_t op);
void c8_set(struct Chip8 *c, uint16_t op);
void insn_x7(struct Chip8 *c, uint16_t op);
void insn_x8(struct Chip8 *c, uint16_t op);
void c8_isDiffXY(struct Chip8 *c, uint16_t op);
void insn_xA(struct Chip8 *c, uint16_t op);
void insn_xB(struct Chip8 *c, uint16_t op);
void insn_xC(struct Chip8 *c, uint16_t op);
void c8_display(struct Chip8 *c, uint16_t op);
void insn_xE(struct Chip8 *c, uint16_t op);
void insn_xF(struct Chip8 *c, uint16_t op);

#define USE_MAJORS_TAB                          \
    static const opfn MAJORS_TAB[MAJORS] = {    \
        insn_x0,                                \
        c8_jump,                                \
        c8_call,                                \
        c8_isEqXNN,                             \
        c8_isDiffXNN,                           \
        c8_isEqXY,                              \
        c8_set,                                 \
        insn_x7,                                \
        insn_x8,                                \
        c8_isDiffXY,                            \
        insn_xA,                                \
        insn_xB,                                \
        insn_xC,                                \
        c8_display,                             \
        insn_xE,                                \
        insn_xF                                 \
    }

#endif /* C8_INTERP_INSTRUCTIONS_H */
