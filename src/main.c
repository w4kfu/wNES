#include "wnes.h"

int init_conf(struct wnes_conf_s *conf, char *rom_name)
{
  if ((conf->sb = malloc(sizeof (struct stat))) == NULL)
    {
      perror("malloc()");
      return (0);
    }
  if ((conf->fd = open(rom_name, O_RDONLY)) == -1)
    {
      free(conf->sb);
      perror("open()");
      return (0);
    }
  if (stat(rom_name, conf->sb) == -1)
    {
      free(conf->sb);
      perror("stat()");
      return (0);
    }
  if ((conf->p = mmap(NULL, conf->sb->st_size, PROT_READ, MAP_PRIVATE,
		      conf->fd, 0)) == MAP_FAILED)
    {
      free(conf->sb);
      perror("mmap()");
      return (0);
    }
  return (1);
}

int main(int argc, char **argv)
{
  struct wnes_conf_s conf;

  if (argc != 2)
    {
      printf ("Usage : %s <rom_file>\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  if (!init_conf(&conf, argv[0]))
    exit(EXIT_FAILURE);
  return (0);
}
