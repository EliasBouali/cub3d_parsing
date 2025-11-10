#include "cubd3.h"

void	init_scene_outputs(t_scene *scene)
{
	scene->textures.no = NULL;
	scene->textures.so = NULL;
	scene->textures.we = NULL;
	scene->textures.ea = NULL;
	scene->fc.floor.blue = 0;
	scene->fc.floor.green = 0;
	scene->fc.floor.red = 0;
	scene->fc.floor.defined = 0;
	scene->fc.ceiling.blue = 0;
	scene->fc.ceiling.green = 0;
	scene->fc.ceiling.red = 0;
	scene->fc.ceiling.defined = 0;
	scene->map.lines_map = NULL;
	scene->map.cols = 0;
	scene->map.rows = 0;
	scene->spawn.col = -1;
	scene->spawn.row = -1;
	scene->spawn.dir = 0;
	scene->err = NULL;
}

void	free_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->no)
	{
		free(textures->no);
		textures->no = NULL;
	}
	if (textures->so)
	{
		free(textures->so);
		textures->so = NULL;
	}
	if (textures->we)
	{
		free(textures->we);
		textures->we = NULL;
	}
	if (textures->ea)
	{
		free(textures->ea);
		textures->ea = NULL;
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->lines_map)
		return ;
	i = 0;
	while (i < map->rows)
	{
		free(map->lines_map[i]);
		i++;
	}
	free(map->lines_map);
	map->lines_map = NULL;
	map->rows = 0;
	map->cols = 0;
}

char	**load_lines(const char *path, t_scene *scene)
{
	int		fd;
	char	*buf;
	char	**lines;

	fd = open_check(path, scene);
	if (fd < 0)
		return (NULL);
	buf = read_file(fd, scene);
	close(fd);
	if (!buf)
		return (NULL);
	lines = split_lines(buf, scene);
	free(buf);
	if (!lines)
		return (NULL);
	return (lines);
}

void	cleanup_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_map(&scene->map);
	free_textures(&scene->textures);
	if (scene->err)
	{
		free(scene->err);
		scene->err = NULL;
	}
}

