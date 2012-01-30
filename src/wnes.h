/**
 ** @file wnes.h
 ** @brief Header file for wnes
 ** @date 29 / 01 / 2012
 ** @author Samuel CHEVET (w4kfu)
 */

#ifndef WNES_H_
# define WNES_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <string.h>

typedef struct wnes_conf_s wnes_conf_s;

# include "rom.h"

struct			wnes_conf_s
{
  char			*name;
  int32_t		fd;
  struct stat		sb;
  char			*p;
  struct header_s	*head_rom;
  struct rom_s		rom;
};

#endif /* !WNES_H_ */
