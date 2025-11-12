#include "cubd3.h"

int	parse_scene(const char *path, t_scene *scene)
{
	char	**lines;
	int		map_start;

	init_scene_outputs(scene);
	lines = load_lines(path, scene);
	if (!lines)
		return (0);
	if (!parse_headers_and_map(lines, scene, &map_start))
		return (0);
	if (!scan_and_set_spawn(scene))
	{
		cleanup_scene(scene);
		return (0);
	}
	if (!finish_map(scene))
	{
		cleanup_scene(scene);
		return (0);
	}
	return (1);
}
