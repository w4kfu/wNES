/**
 ** @file 6502.h
 ** @brief Header for 6502.c
 ** @date 29 / 01 / 2012
 ** @author Samuel CHEVET (w4kfu)
 */

#ifndef M6502_H_
# define M6502_H_

# include "wnes.h"

# define FLAG_CARRY     0x01
# define FLAG_ZERO      0x02
# define FLAG_INTERRUPT 0x04
# define FLAG_DECIMAL   0x08
# define FLAG_BREAK     0x10
# define FLAG_CONSTANT  0x20
# define FLAG_OVERFLOW  0x40
# define FLAG_SIGN      0x80

/* The 6502's 13 addressing modes */
# define IMMED 0 /* Immediate */
# define ABSOL 1 /* Absolute */
# define ZEROP 2 /* Zero Page */
# define IMPLI 3 /* Implied */
# define INDIA 4 /* Indirect Absolute */
# define ABSIX 5 /* Absolute indexed with X */
# define ABSIY 6 /* Absolute indexed with Y */
# define ZEPIX 7 /* Zero page indexed with X */
# define ZEPIY 8 /* Zero page indexed with Y */
# define INDIN 9 /* Indexed indirect (with x) */
# define ININD 10 /* Indirect indexed (with y) */
# define RELAT 11 /* Relative */
# define ACCUM 12 /* Accumulator */

# define ACCUMULATOR	0
# define ABSOLUTE	1
# define ABSOLUTE_X	2
# define ABSOLUTE_Y	3
# define IMMEDIATE	4
# define IMPLIED	5
# define INDIRECT	6
# define INDIRECT_X	7
# define INDIRECT_Y	8
# define RELATIVE	9
# define ZEROPAGE	10
# define ZEROPAGE_X	11
# define ZEROPAGE_Y	12

/* http://www.masswerk.at/6502/6502_instruction_set.html */

static int InstructionOperandTypes[256] = {
  IMPLIED, INDIRECT_X, IMPLIED, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0x00 */
  IMPLIED, IMMEDIATE, ACCUMULATOR, IMMEDIATE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0x08 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X,  ZEROPAGE_X,  ZEROPAGE_X,  ZEROPAGE_X, /* 0x10 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, /* 0x18 */
  ABSOLUTE, INDIRECT_X, IMPLIED, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0x20 */
  IMPLIED, IMMEDIATE, ACCUMULATOR, IMMEDIATE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0x28 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, /* 0x30 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, /* 0x38 */
  IMPLIED, INDIRECT_X, IMPLIED, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0x40 */
  IMPLIED, IMMEDIATE, ACCUMULATOR,  IMMEDIATE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0x48 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, /* 0x50 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, /* 0x58 */
  IMPLIED, INDIRECT_X, IMPLIED, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0x60 */
  IMPLIED, IMMEDIATE, ACCUMULATOR, IMMEDIATE, INDIRECT, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0x68 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, /* 0x70 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, /* 0x78 */
  IMMEDIATE, INDIRECT_X, IMMEDIATE, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0x80 */
  IMPLIED, IMMEDIATE,  IMPLIED, IMMEDIATE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0x88 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_Y, ZEROPAGE_Y, /* 0x90 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_Y, ABSOLUTE_Y, /* 0x98 */
  IMMEDIATE, INDIRECT_X, IMMEDIATE, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0xA0 */
  IMPLIED, IMMEDIATE, IMPLIED, IMMEDIATE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0xA8 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_Y, ZEROPAGE_Y, /* 0xB0 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_Y, ABSOLUTE_Y, /* 0xB8 */
  IMMEDIATE, INDIRECT_X, IMMEDIATE, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0xC0 */
  IMPLIED,  IMMEDIATE, IMPLIED, IMMEDIATE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0xC8 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, /* 0xD0 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, /* 0xD8 */
  IMMEDIATE, INDIRECT_X, IMMEDIATE, INDIRECT_X, ZEROPAGE, ZEROPAGE, ZEROPAGE, ZEROPAGE, /* 0xE0 */
  IMPLIED,  IMMEDIATE, IMPLIED, IMMEDIATE, ABSOLUTE, ABSOLUTE, ABSOLUTE, ABSOLUTE, /* 0xE8 */
  RELATIVE, INDIRECT_Y, IMPLIED, INDIRECT_Y, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, ZEROPAGE_X, /* 0xF0 */
  IMPLIED, ABSOLUTE_Y, IMPLIED, ABSOLUTE_Y, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X, ABSOLUTE_X  /* 0xF8 */
};

static char *InstructionNames[256]  = {
  "brk", "ora", "invalid", "invalid", "invalid", "ora", "asl", "invalid", /* 0x00 */
  "php", "ora", "asl@", "invalid", "invalid", "ora", "asl", "invalid", /* 0x08 */
  "bpl", "ora", "invalid", "invalid", "invalid", "ora", "asl", "invalid", /* 0x10 */
  "clc", "ora", "invalid", "invalid", "invalid", "ora", "asl", "invalid", /* 0x18 */
  "jsr", "and", "invalid", "invalid", "bit", "and", "rol", "invalid", /* 0x20 */
  "plp", "and", "rol@", "invalid", "bit", "and", "rol", "invalid", /* 0x28 */
  "bmi", "and", "invalid", "invalid", "invalid", "and", "rol", "invalid", /* 0x30 */
  "sec", "and", "invalid", "invalid", "invalid", "and", "rol", "invalid", /* 0x38 */
  "rti", "eor", "invalid", "invalid", "invalid", "eor", "lsr", "invalid", /* 0x40 */
  "pha", "eor", "lsr@", "invalid", "jmp", "eor", "lsr", "invalid", /* 0x48 */
  "bvc", "eor", "invalid", "invalid", "invalid", "eor", "lsr", "invalid", /* 0x50 */
  "cli", "eor", "invalid", "invalid", "invalid", "eor", "lsr", "invalid", /* 0x58 */
  "rts", "adc", "invalid", "invalid", "invalid", "adc", "ror", "invalid", /* 0x60 */
  "pla", "adc", "ror@", "invalid", "jmp", "adc", "ror", "invalid", /* 0x68 */
  "bvs", "adc", "invalid", "invalid", "invalid", "adc", "ror", "invalid", /* 0x70 */
  "sei", "adc", "invalid", "invalid", "invalid", "adc", "ror", "invalid", /* 0x78 */
  "invalid", "sta", "invalid", "invalid", "sty", "sta", "stx", "invalid", /* 0x80 */
  "dey", "invalid", "txa", "invalid", "sty", "sta", "stx", "invalid", /* 0x88 */
  "bcc", "sta", "invalid", "invalid", "sty", "sta", "stx", "invalid", /* 0x90 */
  "tya", "sta", "txs", "invalid", "invalid", "sta", "invalid", "invalid", /* 0x98 */
  "ldy", "lda", "ldx", "invalid", "ldy", "lda", "ldx", "invalid", /* 0xa0 */
  "tay", "lda", "tax", "invalid", "ldy", "lda", "ldx", "invalid", /* 0xa8 */
  "bcs", "lda", "invalid", "invalid", "ldy", "lda", "ldx", "invalid", /* 0xb0 */
  "clv", "lda", "tsx", "invalid", "ldy", "lda", "ldx", "invalid", /* 0xb8 */
  "cpy", "cmp", "invalid", "invalid", "cpy", "cmp", "dec", "invalid", /* 0xc0 */
  "iny", "cmp", "dex", "invalid", "cpy", "cmp", "dec", "invalid", /* 0xc8 */
  "bne", "cmp", "invalid", "invalid", "invalid", "cmp", "dec", "invalid", /* 0xd0 */
  "cld", "cmp", "invalid", "invalid", "invalid", "cmp", "dec", "invalid", /* 0xd8 */
  "cpx", "sbc", "invalid", "invalid", "cpx", "sbc", "inc", "invalid", /* 0xe0 */
  "inx", "sbc", "nop", "invalid", "cpx", "sbc", "inc", "invalid", /* 0xe8 */
  "beq", "sbc", "invalid", "invalid", "invalid", "sbc", "inc", "invalid", /* 0xf0 */
  "sed", "sbc", "invalid", "invalid", "invalid", "sbc", "inc", "invalid" /* 0xf8 */
};

int disassemble(struct wnes_conf_s *conf);

#endif /* !M6502_H_ */
