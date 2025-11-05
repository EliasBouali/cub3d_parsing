#include "cubd3.h"

char    *ft_strrchr(const char *s, int c)
{
    int     i;
    char    *last_occurrence;

    if (!s)
        return (0);
    i = 0;
    last_occurrence = NULL;
    while (s[i])
    {
        if (s[i] == (char)c)
        {
            last_occurrence = (char *)&s[i];
        }
        i++;
    }
    if (c == '\0')
        return ((char *)&s[i]);
    return (last_occurrence);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    if (n == 0)
        return (0);
    while (s1[i] && s2[i] && i < (n - 1) && s1[i] == s2[i])
    {
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t  ft_strlen(const char *s)
{
    size_t  i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
    {
        i++;
    }
    return (i);
}

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char           *d;
    const unsigned char     *s;

    if (!dst && !src)
        return (NULL);
    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
    while (n > 0)
    {
        *d = *s;
        d++;
        s++;
        n--;
    }
    return (dst);
}
int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}
