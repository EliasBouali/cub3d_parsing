#include "cubd3.h"

int open_check(const char *path, t_scene *scene)
{
    const char  *dot;
    int         fd;

    if (!path || !*path)
        return (set_parse_error(scene, "No file path provided"), -1);
    dot = ft_strrchr(path, '.');
    if (!dot || dot == path || ft_strncmp(dot, ".cub", 4) != 0 || dot[4] != '\0')
        return (set_parse_error(scene, "Invalid file extension (must be .cub)"), -1);
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (set_parse_error(scene, "Cannot open file (check permissions)"), -1);
    return (fd);
}
