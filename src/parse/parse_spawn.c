#include "cubd3.h"

static int	is_spawn_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	is_neutral_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	return (0);
}

static int	process_line(char *line, int row, t_spawn *spawn, t_scene *scene)
{
	int		i;
	char	c;

	if (!line)
		return (set_parse_error(scene, "Invalid map line"), 0);
	i = 0;
	while (line[i])
	{
		c = line[i];
		if (is_spawn_char(c))
		{
			if (spawn->found)
				return (set_parse_error(scene, "Map contains multiple player starting positions"), 0);
			spawn->found = 1;
			spawn->row = row;
			spawn->col = i;
			spawn->dir = c;
			line[i] = '0';
		}
		else if (!is_neutral_char(c))
			return (set_parse_error(scene, "Map contains invalid character (only 0, 1, N, S, E, W, space allowed)"), 0);
		i++;
	}
	return (1);
}

int	scan_map_for_spawn(t_scene *scene)
{
	int		row;
	t_spawn	sp;

	if (!scene || !scene->map.lines_map || !scene->map.lines_map[0])
		return (set_parse_error(scene, "Invalid map inputs"), 0);
	sp.found = 0;
	row = 0;
	while (scene->map.lines_map[row])
	{
		if (!process_line(scene->map.lines_map[row], row, &sp, scene))
			return (0);
		row++;
	}
	if (!sp.found)
		return (set_parse_error(scene, "Map is missing player starting position (N, S, E, or W)"), 0);
	scene->spawn.row = sp.row;
	scene->spawn.col = sp.col;
	scene->spawn.dir = sp.dir;
	return (1);
}
