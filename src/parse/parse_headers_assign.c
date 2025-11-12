#include "cubd3.h"

int	match_and_set_texture(const char *line, const char *id,
			char **slot, int *seen_flag)
{
	int	status;

	status = match_texture_line(line, id, slot);
	if (status == -1)
		return (-1);
	if (status == 1)
	{
		if (*seen_flag)
			return (-1);
		*seen_flag = 1;
		return (1);
	}
	return (0);
}

int	match_and_set_color(const char *line, char id,
			t_color *slot, int *seen_flag)
{
	int	status;

	status = match_color_line(line, id, slot);
	if (status == 1)
	{
		if (*seen_flag)
			return (-1);
		*seen_flag = 1;
		return (1);
	}
	return (0);
}
