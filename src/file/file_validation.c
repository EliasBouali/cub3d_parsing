#include "cubd3.h"

int open_check(const char *path, t_scene *scene)
{
    const char  *dot;
    int         fd;
    char        c;
    ssize_t     n;

    if (!path || !*path)
        return (set_parse_error(scene, "Invalid path"), -1);
    dot = ft_strrchr(path, '.');
    if (!dot || dot == path || ft_strncmp(dot, ".cub", 4) != 0 || dot[4] != '\0')
        return (set_parse_error(scene, "Invalid extension (.cub required)"), -1);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (set_parse_error(scene, "Cannot open file"), -1);
    n = read(fd, &c, 1);
    if (n <= 0)
    {
        close(fd);
        return (set_parse_error(scene, "Empty or unreadable file"), -1);
    }
    close(fd);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (set_parse_error(scene, "Reopen failed"), -1);
    return (fd);
}
