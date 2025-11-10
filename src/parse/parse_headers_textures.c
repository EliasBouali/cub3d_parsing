#include "cubd3.h"

static int  starts_with_ident(const char **cursor, const char *id)
{
    size_t i;

    if (!cursor || !*cursor || !id)
        return (0);
    i = 0;
    while (id[i] && (*cursor)[i] && (*cursor)[i] == id[i])
        i++;
    if (id[i] != '\0')
        return (0);
    *cursor = *cursor + i;
    return (1);
}

static int  read_path_token_len(const char *s, size_t *out_len)
{
    size_t n;

    if (!s || !out_len)
        return (0);
    n = 0;
    while (s[n] && !is_space(s[n]))
        n++;
    if (n == 0)
        return (0);
    *out_len = n;
    return (1);
}

static int  only_spaces_to_eol(const char *s)
{
    if (!s)
        return (0);
    while (*s && is_space(*s))
        s++;
    if (*s != '\0')
        return (0);
    return (1);
}

static int  alloc_copy_path(const char *start, size_t len, char **out_path)
{
    char *copy;

    copy = (char *)malloc(len + 1);
    if (!copy)
        return (-1);
    if (len > 0)
        ft_memcpy(copy, start, len);
    copy[len] = '\0';
    *out_path = copy;
    return (1);
}


int match_texture_line(const char *line, const char *id, char **out_path)
{
    const char *cursor;
    size_t      path_len;
    int         st;

    if (!line || !id || !out_path)
        return (0);
    *out_path = NULL;
    cursor = line;
    if (!starts_with_ident(&cursor, id))
        return (0);
    if (*cursor == '\0' || !is_space(*cursor))
        return (0);
    skip_spaces(&cursor);
    if (*cursor == '\0')
        return (0);
    if (!read_path_token_len(cursor, &path_len))
        return (0);
    if (cursor[path_len] != '\0' && !only_spaces_to_eol(cursor + path_len))
        return (0);
    st = alloc_copy_path(cursor, path_len, out_path);
    if (st == -1)
        return (-1);
    return (1);
}
