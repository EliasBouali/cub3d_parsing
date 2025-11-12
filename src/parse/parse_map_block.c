#include "cubd3.h"
#include <stdlib.h>

static char	*dup_line(const char *s)
{
	size_t	n;
	char	*dst;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	dst = (char *)malloc(n + 1);
	if (!dst)
		return (NULL);
	if (n)
		ft_memcpy(dst, s, n);
	dst[n] = '\0';
	return (dst);
}

static int	count_map_rows(char **lines, int map_start)
{
	int	i;
	int	rows;

	rows = 0;
	i = map_start;
	while (lines[i])
	{
		rows++;
		i++;
	}
	return (rows);
}

static void	free_partial_map(char **lines_map, int count)
{
	int	k;

	k = 0;
	while (k < count)
		free(lines_map[k++]);
	free(lines_map);
}

static void	reset_map_data(t_map *out)
{
	out->lines_map = NULL;
	out->rows = 0;
	out->cols = 0;
}

static void	update_max_cols(t_map *out, int r)
{
	size_t	len;

	len = ft_strlen(out->lines_map[r]);
	if ((int)len > out->cols)
		out->cols = (int)len;
}

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
