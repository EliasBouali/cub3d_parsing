#include "cubd3.h"


char *read_file(int fd)
{
    char    *buf;
    size_t   capacity;
    size_t   len;
    ssize_t  bytes_read;
    char     tmp[READ_BUFFER];

    buf = NULL;
    capacity = 0;
    len = 0;

    if (fd < 0)
    {
        printf("Error\nInvalid file descriptor\n");
        return NULL;
    }

    while ((bytes_read = read(fd, tmp, READ_BUFFER)) > 0)
    {
        size_t need;

        need = len + (size_t)bytes_read + 1;
        if (need > capacity)
        {
            size_t new_cap;
            if (capacity == 0)
                new_cap = need;
            else
                new_cap = capacity;
            while (new_cap < need)
            {
                if (new_cap > (SIZE_MAX / 2))
                {
                    free(buf);
                    printf("Error\nAllocation overflow\n");
                    return NULL;
                }
                new_cap *= 2;
            }
            char *new_buffer = (char *)malloc(new_cap);
            if (new_buffer == NULL)
            {
                free(buf);
                printf("Error\nAllocation failed\n");
                return NULL;
            }
            if (buf != NULL)
            {
                ft_memcpy(new_buffer, buf, len);
                free(buf);
            }
            buf = new_buffer;
            capacity = new_cap;
        }
        ft_memcpy(buf + len, tmp, (size_t)bytes_read);
        len += (size_t)bytes_read;
    }
    if (bytes_read < 0)
    {
        free(buf);
        printf("Error\nRead error\n");
        return NULL;
    }
    if (len == 0)
    {
        free(buf);
        printf("Error\nEmpty scene file\n");
        return NULL;
    }
    buf[len] = '\0';
    return buf;
}
