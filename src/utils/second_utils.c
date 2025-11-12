#include "cubd3.h"

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
        return (1);
    return (0);
}



void skip_spaces(const char **cursor)
{
  const char *s = *cursor;
  while (*s && is_space(*s))
    s++;
  *cursor = s;
}

int is_empty_line(const char *line)
{
  size_t i;

  if (!line)
    return (1);
  i = 0;
  while (line[i] != '\0')
  {
    if (!is_space(line[i]))
      return 0;
    i++;
  }
  return (1);
}
