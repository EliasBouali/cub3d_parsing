#include "cubd3.h"

int consume_id_and_spaces(const char **cursor, char id)
{
    if (!cursor || !*cursor)
        return (0);
    if (**cursor != id)
        return (0);
    *cursor = *cursor + 1;
    if (**cursor == '\0' || !is_space(**cursor))
        return (0);
    skip_spaces(cursor);
    return (1);
}

int parse_color(const char **cursor, int *out_value)
{
    const char *s;
    long        value;

    if (!cursor || !*cursor || !out_value)
        return (0);
    s = *cursor;
    value = 0;
    if (!ft_isdigit(*s))
        return (0);
    while (ft_isdigit(*s))
    {
        value = value * 10 + (*s - '0');
        if (value > 255)
            return (0);
        s++;
    }
    *out_value = (int)value;
    *cursor = s;
    return (1);
}

int ft_get_char(const char **cursor, char expected)
{
    const char *s;

    if (!cursor || !*cursor)
        return (0);
    s = *cursor;
    skip_spaces(&s);
    if (*s != expected)
        return (0);
    s++;
    *cursor = s;
    return (1);
}
int  parse_rgb_triplet(const char **cursor, int *red, int *green, int *blue)
{
    if (!parse_color(cursor, red))
        return (0);
    if (!ft_get_char(cursor, ','))
        return (0);
    if (!parse_color(cursor, green))
        return (0);
    if (!ft_get_char(cursor, ','))
        return (0);
    if (!parse_color(cursor, blue))
        return (0);
    skip_spaces(cursor);
    return (1);
}
int match_color_line(const char *line, char id, t_color *out)
{
    const char *cursor;
    int         r;
    int         g;
    int         b;

    if (!line || !out)
        return (0);
    cursor = line;
    if (!consume_id_and_spaces(&cursor, id))
        return (0);
    if (!parse_rgb_triplet(&cursor, &r, &g, &b))
        return (0);
    if (*cursor != '\0')
        return (0);
    out->red = r;
    out->green = g;
    out->blue = b;
    out->defined = 1;
    return (1);
}
