#include "cubd3.h"

char	*dup_line(const char *s)
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

int	count_map_rows(char **lines, int map_start)
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

void	free_partial_map(char **lines_map, int count)
{
	int	k;

	k = 0;
	while (k < count)
		free(lines_map[k++]);
	free(lines_map);
}

void	reset_map_data(t_map *out)
{
	out->lines_map = NULL;
	out->rows = 0;
	out->cols = 0;
}

void	update_max_cols(t_map *out, int r)
{
	size_t	len;

	len = ft_strlen(out->lines_map[r]);
	if ((int)len > out->cols)
		out->cols = (int)len;
}
