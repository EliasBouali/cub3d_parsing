#include "cubd3.h"

static void free_map_lines(char **lines_map, int count)
{
  int i;

  i = 0;
  if (!lines_map)
    return ;
  while (i < count)
  {
    free(lines_map[i]);
    i++;
  }
  free(lines_map);
}

int parse_map_block(char **lines, int map_start, t_map *out)
{
    int   i;
    int   start;
    int   end;
    int   raw_count;
    int   map_rows;
    char **lines_map;

    if (!lines || map_start < 0 || !out)
    {
        printf("Error\nInvalid map inputs\n");
        return 0;
    }
    raw_count = 0;
    i = map_start;
    while (lines[i] != NULL)
    {
        raw_count++;
        i++;
    }
    if (raw_count == 0)
    {
        printf("Error\nNo map found\n");
        return 0;
    }
    start = map_start;
    while (lines[start] != NULL && is_empty_line(lines[start]))
        start++;
    end = map_start + raw_count - 1;
    while (end >= start && is_empty_line(lines[end]))
        end--;
    if (end < start)
    {
        printf("Error\nNo map found\n");
        return 0;
    }
    map_rows = end - start + 1;
    lines_map = (char **)malloc(sizeof(char *) * (map_rows + 1));
    if (!lines_map)
    {
        printf("Error\nAllocation failed\n");
        return 0;
    }
    i = 0;
    while (i < map_rows)
    {
        const char *src = lines[start + i];
        size_t len = ft_strlen(src);

        lines_map[i] = (char *)malloc(len + 1);
        if (!lines_map[i])
        {
            printf("Error\nAllocation failed\n");
            free_map_lines(lines_map, i);
            return 0;
        }
        ft_memcpy(lines_map[i], src, len);
        lines_map[i][len] = '\0';
        i++;
    }
    lines_map[map_rows] = NULL;
    out->lines_map = lines_map;
    out->rows = map_rows;
    out->cols = 0;
    return 1;
}
