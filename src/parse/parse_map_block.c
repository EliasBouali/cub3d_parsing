#include "cubd3.h"
#include <stdlib.h>



static int	copy_map_lines(char **lines, int map_start,
				t_map *out, t_scene *scene)
{
	int	r;
	int	i;

	r = 0;
	i = map_start;
	while (r < out->rows)
	{
		out->lines_map[r] = dup_line(lines[i]);
		if (!out->lines_map[r])
		{
			free_partial_map(out->lines_map, r);
			reset_map_data(out);
			return (set_parse_error(scene, "OOM map line"), 0);
		}
		update_max_cols(out, r);
		r++;
		i++;
	}
	return (1);
}

int	parse_map_block(char **lines, int map_start, t_map *out, t_scene *scene)
{
	int	rows;

	(void)scene;
	rows = count_map_rows(lines, map_start);
	if (rows <= 0)
		return (set_parse_error(scene, "Empty map block"), 0);
	out->lines_map = (char **)malloc(sizeof(char *) * rows);
	if (!out->lines_map)
		return (set_parse_error(scene, "OOM map lines"), 0);
	out->rows = rows;
	out->cols = 0;
	if (!copy_map_lines(lines, map_start, out, scene))
		return (0);
	return (1);
}
