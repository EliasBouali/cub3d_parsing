#include "cubd3.h"

static int neighbor_is_space(char **lines_map, int row, int col)
{
  if (lines_map[row - 1][col] == ' ')
    return (1);
  if (lines_map[row + 1][col] == ' ')
    return (1);
  if (lines_map[row][col - 1] == ' ')
    return (1);
  if (lines_map[row][col + 1] == ' ')
    return (1);
  return (0);
}

int check_map_closed(t_map *map)
{
  int row;
  int col;
  char c;

  if (!map || !map->lines_map)
    return (0);
  row = 0;
  while (row < map->rows)
  {
    col = 0;
    while (col < map->cols)
    {
      c = map->lines_map[row][col];
      if (c == '0')
      {
        if (neighbor_is_space(map->lines_map, row, col))
          return (0);
      }
      col++;
    }
    row++;
  }
  return (1);
}
