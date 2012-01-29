/**
 ** @file rom.h
 ** @brief Header file for rom.c
 ** @date 29 / 01 / 2012
 ** @author Samuel CHEVET (w4kfu)
 */

#ifndef ROM_H_
# define ROM_H_

# include "wnes.h"

struct		header_s
{
  uint8_t	magic[4];
  uint8_t	PRG_ROM_size;
  uint8_t	CHR_ROM_size;
  uint8_t	flags_6;
  uint8_t	flags_7;
  uint8_t	PRG_RAM_size;
  uint8_t	flags_9;
  uint8_t	zerobytes[5];
};



#endif /* !ROM_H_ */
