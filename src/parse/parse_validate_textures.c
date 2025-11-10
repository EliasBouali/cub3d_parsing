#include "cubd3.h"

static int  file_is_readable(const char *path)
{
    int fd;

    if (path == NULL || path[0] == '\0')
        return (0);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
}

int validate_textures_exist(t_textures *tx)
{
    if (tx == NULL)
        return (0);
    if (!file_is_readable(tx->no))
        return (0);
    if (!file_is_readable(tx->so))
        return (0);
    if (!file_is_readable(tx->we))
        return (0);
    if (!file_is_readable(tx->ea))
        return (0);
    return (1);
}
