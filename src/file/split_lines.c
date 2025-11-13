#include "cubd3.h"


static int	fill_lines_array(const char *filebuf, char **lines, t_scene *scene)
{
	size_t	indexes[3];
	char	c;

	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
	while (1)
	{
		c = filebuf[indexes[0]];
		if (c == '\n' || c == '\0')
		{
			if (!process_line_split(filebuf, lines, indexes, scene))
				return (0);
			if (c == '\0')
				break ;
		}
		indexes[0]++;
	}
	lines[indexes[2]] = NULL;
	return (1);
}

char	**split_lines(const char *filebuf, t_scene *scene)
{
	char	**lines;
	size_t	total_lines;

	if (filebuf == NULL)
	{
		set_parse_error(scene, "Invalid buffer");
		return (NULL);
	}
	total_lines = count_total_lines(filebuf);
	lines = alloc_lines_array(total_lines, scene);
	if (!lines)
		return (NULL);
	if (total_lines == 0)
		return (lines);
	if (!fill_lines_array(filebuf, lines, scene))
		return (NULL);
	return (lines);
}
