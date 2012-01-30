/**
 ** @file main.c
 ** @brief Main program for wNES emulator
 ** @date 29 / 01 / 2012
 ** @author Samuel CHEVET (w4kfu)
 */

#include "wnes.h"

int init_conf(struct wnes_conf_s *conf, char *rom_name)
{
  if ((conf->fd = open(rom_name, O_RDONLY)) == -1)
    {
      perror("open()");
      return (0);
    }
  if (stat(rom_name, &conf->sb) == -1)
    {
      close(conf->fd);
      perror("stat()");
      return (0);
    }
  if ((conf->p = mmap(NULL, conf->sb.st_size, PROT_READ, MAP_PRIVATE,
		      conf->fd, 0)) == MAP_FAILED)
    {
      close(conf->fd);
      perror("mmap()");
      return (0);
    }
  conf->rom.has_trainer = 0;
  return (1);
}

void free_all(struct wnes_conf_s *conf)
{
  free(conf->name);
  munmap(conf->p, conf->sb.st_size);
  close(conf->fd);
}

int main(int argc, char *argv[])
{
  struct wnes_conf_s conf;

  if (argc != 2)
    {
      printf ("Usage : %s <rom_file>\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  if (!(conf.name = strdup(argv[1])))
    exit(EXIT_FAILURE);
  if (!init_conf(&conf, argv[1]))
    exit(EXIT_FAILURE);
  if (!load_rom(&conf))
    exit(EXIT_FAILURE);
  free_all(&conf);
  return (0);
}
