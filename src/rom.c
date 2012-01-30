/**
 ** @file rom.c
 ** @brief File for reading, checking and filling rom
 ** @date 29 / 01 / 2012
 ** @author Samuel CHEVET (w4kfu)
 */

#include "wnes.h"

int		load_rom(struct wnes_conf_s *conf)
{
  char		sig_ines[4] = { 'N', 'E', 'S', 0x1A };
  uint32_t	off = 0;

  conf->head_rom = (struct header_s*)conf->p;
  if (memcmp((void*)conf->head_rom, (void*)sig_ines, 4))
    {
      printf("Not a valid header\n");
      return(0);
    }
  printf("PRG_ROM size = %d\n", conf->head_rom->PRG_ROM_size << 4);
  printf("CHR_ROM size = %d\n", conf->head_rom->CHR_ROM_size);
  printf("Flag 6 = %d\n", conf->head_rom->flags_6);
  printf("Flag 7 = %d\n", conf->head_rom->flags_7);
  printf("PRG_RAM size = %d\n", conf->head_rom->PRG_RAM_size);
  printf("Flag 9 = %d\n", conf->head_rom->flags_9);
  if (!conf->head_rom->PRG_ROM_size)
    {
      printf("[-] No PRG data\n");
      return (0);
    }
  if (conf->head_rom->flags_6 & 4)
    {
      conf->rom.has_trainer = 1;
      off = 512;
      printf("Has trainer\n");
    }
  if (!conf->rom.has_trainer)
    {
      conf->rom.PRG_ROM = conf->p + 16 + off;
      if (conf->head_rom->CHR_ROM_size)
	conf->rom.CHR_ROM = conf->p + 16
	  + (conf->head_rom->PRG_ROM_size << 10) + off;
    }
  return (1);
}
