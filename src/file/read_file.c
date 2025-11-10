#include "cubd3.h"

typedef struct s_file_reader
{
	char	*data;
	size_t	capacity;
	size_t	length;
	t_scene	*scene;
}	t_file_reader;

static int	reader_fail(t_file_reader *reader, const char *msg)
{
	if (reader->data)
	{
		free(reader->data);
		reader->data = NULL;
	}
	set_parse_error(reader->scene, msg);
	return (0);
}

static int	reader_realloc(t_file_reader *reader, size_t new_capacity)
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

static int	reader_ensure_capacity(t_file_reader *reader, size_t need)
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

static void	reader_init(t_file_reader *reader, t_scene *scene)
{
	reader->data = NULL;
	reader->capacity = 0;
	reader->length = 0;
	reader->scene = scene;
}

static int	reader_append_chunk(t_file_reader *reader,
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

static char	*reader_finish(t_file_reader *reader, ssize_t last_read_status)
{
	if (last_read_status < 0)
		return (reader_fail(reader, "Read error"), NULL);
	if (reader->length == 0)
		return (reader_fail(reader, "Empty or unreadable file"), NULL);
	reader->data[reader->length] = '\0';
	return (reader->data);
}

char	*read_file(int fd, t_scene *scene)
{
	t_file_reader	reader;
	ssize_t			bytes_read;
	char			chunk_buf[READ_BUFFER];

	if (fd < 0)
	{
		set_parse_error(scene, "Invalid file descriptor");
		return (NULL);
	}
	reader_init(&reader, scene);
	bytes_read = read(fd, chunk_buf, READ_BUFFER);
	while (bytes_read > 0)
	{
		if (!reader_append_chunk(&reader, chunk_buf, bytes_read))
			return (NULL);
		bytes_read = read(fd, chunk_buf, READ_BUFFER);
	}
	return (reader_finish(&reader, bytes_read));
}
