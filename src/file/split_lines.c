#include "cubd3.h"

static void	free_partial(char **lines, size_t n)
{
	if (lines == NULL)
		return ;
	while (n > 0)
	{
		n--;
		free(lines[n]);
	}
	free(lines);
}

static size_t	count_total_lines(const char *filebuf)
{
	size_t	i;
	size_t	count_nl;

	if (filebuf[0] == '\0')
		return (0);
	i = 0;
	count_nl = 0;
	while (filebuf[i])
	{
		if (filebuf[i] == '\n')
			count_nl++;
		i++;
	}
	return (count_nl + 1);
}

static char	**alloc_lines_array(size_t total_lines, t_scene *scene)
{
	char	**lines;

	lines = (char **)malloc(sizeof(char *) * (total_lines + 1));
	if (!lines)
	{
		set_parse_error(scene, "Allocation failed (lines array)");
		return (NULL);
	}
	if (total_lines == 0)
	{
		lines[0] = NULL;
		return (lines);
	}
	return (lines);
}

static char	*alloc_line(const char *filebuf, size_t start, size_t end)
{
	char	*line;
	size_t	len;

	if (end > start)
		len = end - start;
	else
		len = 0;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	if (len > 0)
		ft_memcpy(line, filebuf + start, len);
	line[len] = '\0';
	return (line);
}

static int	process_line_split(const char *filebuf, char **lines,
				size_t *indexes, t_scene *scene)
{
	char	*line;
	size_t	end;

	end = indexes[0];
	line = alloc_line(filebuf, indexes[1], end);
	if (!line)
	{
		free_partial(lines, indexes[2]);
		set_parse_error(scene, "Allocation failed (line)");
		return (0);
	}
	lines[indexes[2]] = line;
	indexes[2]++;
	indexes[1] = indexes[0] + 1;
	return (1);
}

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
