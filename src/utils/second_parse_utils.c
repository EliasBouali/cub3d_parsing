#include "cubd3.h"

int	finish_map(t_scene *scene)
{
	if (!make_map_rectangular(&scene->map))
		return (0);
	if (!check_map_closed(&scene->map))
		return (0);
	if (!validate_textures_exist(&scene->textures))
		return (0);
	return (1);
}

int	parse_headers_and_map(char **lines, t_scene *scene, int *map_start)
{
	if (!parse_headers(lines, map_start, scene))
	{
		free(lines);
		return (0);
	}
	if (!parse_map_block(lines, *map_start, &scene->map, scene))
	{
		free(lines);
		free_textures(&scene->textures);
		return (0);
	}
	free(lines);
	return (1);
}

int	scan_and_set_spawn(t_scene *scene)
{
	if (!scan_map_for_spawn(scene))
		return (0);
	return (1);
}

