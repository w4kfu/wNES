/**
 ** @file rom.c
 ** @brief Core file for 6502 microprocessor
 ** @date 29 / 01 / 2012
 ** @author Samuel CHEVET (w4kfu)
 */

# include "wnes.h"

int	disassemble(struct wnes_conf_s *conf)
{
  int		pc = 0;
  uint8_t	opcode = 0;
  uint8_t	tmp_byte1;
  int		origin = 0x8000;
  uint16_t	prg_count = 0;
  word		tmp_word;

  prg_count = (uint16_t)conf->head_rom->PRG_ROM_size << 10;

  origin += 15;

  printf("prg_coumt = %d\n", prg_count);
  for (pc = 0; pc < prg_count;)
    {
      opcode = conf->rom.PRG_ROM[pc];
      if (!strcmp("invalid", InstructionNames[opcode]))
	{
	  pc++;
	  printf("$%04X> %02X:\t.byte $%02x\t\t; INVALID OPCODE !!!\n",
		 origin + pc, opcode, opcode);
	  continue;
	}
      switch(InstructionOperandTypes[opcode])
	{
	case ACCUMULATOR:
	  pc++;
	  printf("$%04X> %02X:\t%s A\t\t;\n", origin + pc - 1, opcode,
		 InstructionNames[opcode]);
	  break;
	case ABSOLUTE:
	  pc++;
	  tmp_word.b.l = conf->rom.PRG_ROM[pc];
	  pc++;
	  tmp_word.b.h = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X%02X:\t%s $%02X%02X\t;\n", origin + pc - 2,
		 opcode, tmp_word.b.l, tmp_word.b.h, InstructionNames[opcode],
		 tmp_word.b.h, tmp_word.b.l);
	  pc++;
	  break;

	case ABSOLUTE_X:
	  pc++;
	  tmp_word.b.l = conf->rom.PRG_ROM[pc];
	  pc++;
	  tmp_word.b.h = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X%02X:\t%s $%02X%02X,X\t;\n", origin + pc - 2,
		 opcode, tmp_word.b.l, tmp_word.b.h, InstructionNames[opcode],
		 tmp_word.b.l, tmp_word.b.h);
	  pc++;
	  break;

	case ABSOLUTE_Y:
	  pc++;
	  tmp_word.b.l = conf->rom.PRG_ROM[pc];
	  pc++;
	  tmp_word.b.h = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X%02X:\t%s $%02X%02X,Y\t;\n", origin + pc - 2,
		 opcode, tmp_word.b.l, tmp_word.b.h, InstructionNames[opcode],
		 tmp_word.b.l, tmp_word.b.h);
	  pc++;
	  break;

	case IMMEDIATE:
	  pc++;
	  tmp_byte1 = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X:\t%s #$%02X\t;\n", origin + pc - 1, opcode,
		 tmp_byte1, InstructionNames[opcode], tmp_byte1);
	  pc++;
	  break;

	case IMPLIED:
	  pc++;
	  printf("$%04X> %02X:\t%s\t\t;\n", origin + pc - 1, opcode,
		 InstructionNames[opcode]);
	  break;

	case INDIRECT:
	  pc++;
	  tmp_word.b.l = conf->rom.PRG_ROM[pc];
	  pc++;
	  tmp_word.b.h = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X%02X:\t%s ($%02X%02X)\t;\n", origin + pc - 2,
		 opcode, tmp_word.b.l, tmp_word.b.h, InstructionNames[opcode],
		 tmp_word.b.l, tmp_word.b.h);
	  pc++;
	  break;

	case INDIRECT_X:
	  pc++;
	  tmp_byte1 = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X:\t%s ($%02X,X)\t\t;\n", origin + pc - 1,
		 opcode, tmp_byte1, InstructionNames[opcode], tmp_byte1);
	  pc++;
	  break;

	case INDIRECT_Y:
	  pc++;
	  tmp_byte1 = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X:\t%s ($%02X,Y)\t\t;\n", origin + pc - 1,
		 opcode, tmp_byte1, InstructionNames[opcode], tmp_byte1);
	  pc++;
	  break;

	case RELATIVE:
	  pc++;
	  tmp_byte1 = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X:\t%s $%04X\t;\n", origin + pc - 1, opcode,
		 tmp_byte1, InstructionNames[opcode], (origin + pc)
		 + (int8_t)(tmp_byte1) + 1);
	  pc++;
	  break;

	case ZEROPAGE:
	  pc++;
	  tmp_byte1 = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X:\t%s $%02X\t\t;\n", origin + pc - 1, opcode,
		 tmp_byte1, InstructionNames[opcode], tmp_byte1);
	  pc++;
	  break;

	case ZEROPAGE_X:
	  pc++;
	  tmp_byte1 = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X:\t%s $%02X,X\t\t;\n", origin + pc - 1, opcode,
		 tmp_byte1, InstructionNames[opcode], tmp_byte1);
	  pc++;
	  break;

	case ZEROPAGE_Y:
	  pc++;
	  tmp_byte1 = conf->rom.PRG_ROM[pc];
	  printf("$%04X> %02X %02X:\t%s $%02XY\t\t;\n", origin + pc - 1, opcode,
		 tmp_byte1, InstructionNames[opcode], tmp_byte1);
	  pc++;
	  break;

	default:
	  printf("WTF I'M DOING HERE ?\n");
	  break;
	}
    }
  printf("%d", InstructionOperandTypes[0]);
  printf("%s", InstructionNames[0]);
  return (0);
}
