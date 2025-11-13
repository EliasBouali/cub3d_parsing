#include "cubd3.h"

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
	char			read_buffer[READ_BUFFER];

	if (fd < 0)
	{
		set_parse_error(scene, "Invalid file descriptor");
		return (NULL);
	}
	reader_init(&reader, scene);
	bytes_read = read(fd, read_buffer, READ_BUFFER);
	while (bytes_read > 0)
	{
		if (!reader_append_buffer(&reader, read_buffer, bytes_read))
			return (NULL);
		bytes_read = read(fd, read_buffer, READ_BUFFER);
	}
	return (reader_finish(&reader, bytes_read));
}
