#include "cubd3.h"

static void free_partial(char **lines, size_t n)
{
    if (lines == NULL)
        return;
    while (n > 0)
    {
        n--;
        free(lines[n]);
    }
    free(lines);
}

char **split_lines(const char *filebuf, t_scene *scene)
{
    char    **lines;
    size_t  i;
    size_t  j;
    size_t  start;
    size_t  end;
    size_t  len;
    size_t  count_nl;
    size_t  total_lines;
    char    *line;
    char    c;

    start = 0;
    j = 0;
    if (filebuf == NULL)
    {
        set_parse_error(scene, "Invalid input buffer");
        return NULL;
    }
    if (filebuf[0] == '\0')
        total_lines = 0;
    else
    {
        i = 0;
        count_nl = 0;
        while (filebuf[i])
        {
            if (filebuf[i] == '\n')
                count_nl++;
            i++;
        }
        total_lines = count_nl + 1;
    }
    lines = (char **)malloc(sizeof(char *) * (total_lines + 1));
    if (!lines)
    {
        set_parse_error(scene, "Allocation failed (lines array)");
        return NULL;
    }
    if (total_lines == 0)
    {
        lines[0] = NULL;
        return lines;
    }
    i = 0;
    while (1)
    {
        c = filebuf[i];
        if (c == '\n' || c == '\0')
        {
            end = i;
            if (end > start)
                len = end - start;
            else
                len = 0;
            line = (char *)malloc(len + 1);
            if (!line)
            {
                free_partial(lines, j);
                set_parse_error(scene, "Allocation failed (line)");
                return NULL;
            }
            if (len > 0)
                ft_memcpy(line, filebuf + start, len);
            line[len] = '\0';
            lines[j] = line;
            j++;
            if (c == '\0')
                break;
            start = i + 1;
        }
        i++;
    }
    lines[j] = NULL;
    return lines;
}

