#include "cubd3.h"


static int print_error(const char *msg)
{
  printf("Error\n%s\n", msg);
  return (-1);
}

int open_check(const char *path)
{
  const char *dot;
  int fd;
  char c;
  ssize_t bytes_read;

  if (!path || !*path)
    return (print_error("Invalid path"));
  dot = ft_strrchr(path, '.');
  if (!dot || dot == path || ft_strncmp(dot, ".cub", 4) != 0 || dot[4] != '\0')
    return (print_error("Invalid extension"));
  fd = open(path, O_RDONLY);
  if (fd < 0)
    return (print_error("Can not open file"));
  bytes_read = read(fd, &c, 1);
  if (bytes_read <= 0)
  {
    close(fd);
    return (print_error("Invalid lectur file"));
  }
  close(fd);
  fd = open(path, O_RDONLY);
  if (fd < 0)
    return (print_error("Can not open file"));
  return (fd);
}
