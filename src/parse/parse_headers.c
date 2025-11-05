#include "cubd3.h"

int match_texture_line(const char *line, const char *ident, char **out_path)
{
    const char *cursor;
    size_t      id_len;
    size_t      path_len;
    char       *path_copy;
    const char *after_path;

    if (!line || !ident || !out_path)
        return (0);
    *out_path = NULL;

    id_len = ft_strlen(ident);
    if (ft_strncmp(line, ident, id_len) != 0)
        return (0);
    cursor = line + id_len;
    if (*cursor == '\0')
        return (0);
    if (!is_space(*cursor))
        return (0);
    skip_spaces(&cursor);
    if (*cursor == '\0')
        return (0);
    path_len = 0;
    while (cursor[path_len] && !is_space(cursor[path_len]))
        path_len++;
    if (path_len == 0)
        return (0);
    if (cursor[path_len] != '\0')
    {
        after_path = cursor + path_len;
        while (*after_path && is_space(*after_path))
            after_path++;
        if (*after_path != '\0')
            return (0);
    }
    path_copy = (char *)malloc(path_len + 1);
    if (!path_copy)
    {
        printf("Error\nAllocation failed\n");
        return (-1);
    }
    if (path_len > 0)
        ft_memcpy(path_copy, cursor, path_len);
    path_copy[path_len] = '\0';
    *out_path = path_copy;
    return (1);
}

int parse_color(const char **cursor, int *out_value)
{
  const char *num_ptr;
  long value;

  if (!cursor || !*cursor || !out_value)
    return (0);
  num_ptr = *cursor;
  value = 0;
  if (!ft_isdigit(*num_ptr))
    return (0);
  while (ft_isdigit(*num_ptr))
  {
    value = value * 10 + (*num_ptr - '0');
    if (value > 255)
      return (0);
    num_ptr++;
  }
  *out_value = (int)value;
  *cursor = num_ptr;
  return (1);
}

int ft_get_char(const char **cursor, char expected)
{
  const char *s;

  if (!cursor || !*cursor)
    return (0);
  s = *cursor;
  skip_spaces(&s);
  if (*s != expected)
    return (0);
  s++;
  *cursor = s;
  return (1);
}

int match_color_line(const char *line, char id, t_color *out)
{
  const char *cursor;
  int r;
  int g;
  int b;

  if (!line || ! out)
    return (0);
  if (line[0] != id)
    return (0);
  cursor = line + 1;
  if (!is_space(*cursor))
    return (0);
  skip_spaces(&cursor);
  if (!parse_color(&cursor, &r))
    return (0);
  if (!ft_get_char(&cursor, ','))
    return (0);
  if (!parse_color(&cursor, &g))
    return 0;
  if (!ft_get_char(&cursor, ','))
    return (0);
  if (!parse_color(&cursor, &b))
    return 0;
  skip_spaces(&cursor);
  if (*cursor != '\0')
    return (0);
  out->red = r;
  out->green = g;
  out->blue = b;
  out->defined = 1;
  return 1;
}

int headers_is_complete(t_seen *s)
{
  if (s->no && s->so && s->we && s->ea && s->f && s->c)
    return 1;
  return 0;
}

int match_and_set_texture(const char *line, const char *id, char **slot, int *seen_flag)
{
  int status;

  status = match_texture_line(line, id, slot);
  if (status == -1)
    return (-1);
  if (status == 1)
  {
    if (*seen_flag)
    {
      printf("Error\nelement already exists\n");
      return (-1);
    }
    *seen_flag = 1;
    return (1);
  }
  return (0);
}

int match_and_set_color(const char *line, char id, t_color *slot, int *seen_flag)
{
  int status;

  status = match_color_line(line, id, slot);
  if (status == 1)
  {
    if (*seen_flag)
    {
      printf("Error\nelement already exists\n");
      return (-1);
    }
    *seen_flag = 1;
    return (1);
  }
  return (0);
}

int dispatch_header_line(const char *line, t_textures *wall_textures, t_fc_colors *floor_ceiling, t_seen *seen)
{
  int status;

  status = match_and_set_texture(line, "NO", &wall_textures->no, &seen->no);
  if (status != 0)
    return status;
  status = match_and_set_texture(line, "SO", &wall_textures->so, &seen->so);
  if (status != 0)
    return status;
  status = match_and_set_texture(line, "WE", &wall_textures->we, &seen->we);
  if (status != 0)
    return status;
  status = match_and_set_texture(line, "EA", &wall_textures->ea, &seen->ea);
  if (status != 0)
    return status;
  status = match_and_set_color(line, 'F', &floor_ceiling->floor, &seen->f);
  if (status != 0)
    return status;
  status = match_and_set_color(line, 'C', &floor_ceiling->ceiling, &seen->c);
  if (status != 0)
    return status;
  return 0;
}

int find_starting_map(char **lines, int i)
{
  while (lines[i] && is_empty_line(lines[i]))
    i++;
  if (lines[i] == NULL)
    return (-1);
  return i;
}
void init_headers_outputs(t_textures *wall_textures,
                                 t_fc_colors *floor_ceiling,
                                 t_seen *seen, int *i)
{
    wall_textures->no = NULL;
    wall_textures->so = NULL;
    wall_textures->we = NULL;
    wall_textures->ea = NULL;
    floor_ceiling->floor.defined = 0;
    floor_ceiling->ceiling.defined = 0;
    seen->no = 0;
    seen->so = 0;
    seen->we = 0;
    seen->ea = 0;
    seen->f = 0;
    seen->c = 0;
    *i = 0;
}

int parse_headers(char **lines, int *out_map_start,
                  t_textures *wall_textures, t_fc_colors *floor_ceiling)
{
    t_seen seen;
    int    i;
    int    status;

    init_headers_outputs(wall_textures, floor_ceiling, &seen, &i);
    while (lines[i] && !headers_is_complete(&seen))
    {
        if (is_empty_line(lines[i])) { i++; continue; }
        status = dispatch_header_line(lines[i], wall_textures, floor_ceiling, &seen);
        if (status == -1)
          return 0;
        if (status == 0)
          { printf("Error\nInvalid identifier\n"); return 0; }
        i++;
    }
    if (!headers_is_complete(&seen))
      { printf("Error\nMissing elements\n"); return 0; }
    i = find_starting_map(lines, i);
    if (i < 0)
      { printf("Error\nNo map found\n"); return 0; }
    *out_map_start = i;
    return 1;
}
