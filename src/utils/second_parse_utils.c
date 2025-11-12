#include "cubd3.h"

static int validate_path_readable(const char *p)
{
    int fd;
    if (!p || !*p)
      return 0;
    fd = open(p, O_RDONLY);
    if (fd < 0)
      return 0;
    close(fd);
    return 1;
}

int parse_headers_and_map(char **lines, t_scene *scene, int *map_start)
{
    if (!parse_headers(lines, map_start, scene))
    {
        free_lines(lines);
        return 0;
    }
    if (!parse_map_block(lines, *map_start, &scene->map, scene))
    {
        free_lines(lines);
        return 0;
    }
    free_lines(lines);
    return 1;
}

int scan_and_set_spawn(t_scene *scene)
{
    if (!scan_map_for_spawn(scene))
        return 0;
    return 1;
}

int finish_map(t_scene *scene)
{
    if (!make_map_rectangular(&scene->map))
        return 0;

    if (!check_map_closed(&scene->map))
        return (set_parse_error(scene,
                "Map is not properly closed by walls"), 0);
    if (!scene->textures.no || !validate_path_readable(scene->textures.no))
        return (set_parse_error(scene,
            "North texture file not found or not readable"), 0);
    if (!scene->textures.so || !validate_path_readable(scene->textures.so))
        return (set_parse_error(scene,
            "South texture file not found or not readable"), 0);
    if (!scene->textures.we || !validate_path_readable(scene->textures.we))
        return (set_parse_error(scene,
            "West texture file not found or not readable"), 0);
    if (!scene->textures.ea || !validate_path_readable(scene->textures.ea))
        return (set_parse_error(scene,
            "East texture file not found or not readable"), 0);

    return 1;
}
