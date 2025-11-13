#include "cubd3.h"

int	reader_fail(t_file_reader *reader, const char *msg)
{
	if (reader->data)
	{
		free(reader->data);
		reader->data = NULL;
	}
	set_parse_error(reader->scene, msg);
	return (0);
}

int	reader_realloc(t_file_reader *reader, size_t new_capacity)
{
	char	*new_data;

	new_data = (char *)malloc(new_capacity);
	if (!new_data)
		return (reader_fail(reader, "Allocation failed"));
	if (reader->data)
	{
		ft_memcpy(new_data, reader->data, reader->length);
		free(reader->data);
	}
	reader->data = new_data;
	reader->capacity = new_capacity;
	return (1);
}

int	reader_ensure_capacity(t_file_reader *reader, size_t need)
{
	size_t	new_capacity;

	if (reader->capacity == 0)
		new_capacity = need;
	else
		new_capacity = reader->capacity;
	while (new_capacity < need)
	{
		if (new_capacity > SIZE_MAX / 2)
			return (reader_fail(reader, "Allocation overflow"));
		new_capacity *= 2;
	}
	return (reader_realloc(reader, new_capacity));
}

void	reader_init(t_file_reader *reader, t_scene *scene)
{
	reader->data = NULL;
	reader->capacity = 0;
	reader->length = 0;
	reader->scene = scene;
}

int	reader_append_buffer(t_file_reader *reader,
								char *chunk_buf, ssize_t bytes_read)
{
	size_t	need;

	need = reader->length + (size_t)bytes_read + 1;
	if (need > reader->capacity && !reader_ensure_capacity(reader, need))
		return (0);
	ft_memcpy(reader->data + reader->length, chunk_buf, (size_t)bytes_read);
	reader->length += (size_t)bytes_read;
	return (1);
}
