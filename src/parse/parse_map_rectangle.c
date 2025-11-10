#include "cubd3.h"

static int  pad_line_with_spaces(char **line_ptr, size_t len, size_t target_width)
{
    char    *old;
    char    *newl;
    size_t  i;

    if (len >= target_width)
        return (1);
    newl = (char *)malloc(target_width + 1);
    if (newl == NULL)
        return (0);
    if (len > 0)
        ft_memcpy(newl, *line_ptr, len);
    i = len;
    while (i < target_width)
    {
        newl[i] = ' ';
        i++;
    }
    newl[target_width] = '\0';
    old = *line_ptr;
    *line_ptr = newl;
    free(old);
    return (1);
}

static size_t get_max_cols(char **lines, int rows)
{
    size_t  max_cols;
    size_t  len;
    int     row;

    max_cols = 0;
    row = 0;
    while (row < rows)
    {
        len = ft_strlen(lines[row]);
        if (len > max_cols)
            max_cols = len;
        row++;
    }
    return (max_cols);
}

static int pad_all_lines(char **lines, int rows, size_t max_cols)
{
    size_t  len;
    int     row;

    row = 0;
    while (row < rows)
    {
        len = ft_strlen(lines[row]);
        if (len < max_cols)
        {
            if (!pad_line_with_spaces(&lines[row], len, max_cols))
                return (0);
        }
        row++;
    }
    return (1);
}

int make_map_rectangular(t_map *map)
{
    size_t  max_cols;

    if (map == NULL || map->lines_map == NULL)
        return (0);
    max_cols = get_max_cols(map->lines_map, map->rows);
    if (!pad_all_lines(map->lines_map, map->rows, max_cols))
        return (0);
    map->cols = (int)max_cols;
    return (1);
}
