#include "cubd3.h"

static void init_headers_state(t_seen *seen, int *i)
{
    seen->no = 0;
    seen->so = 0;
    seen->we = 0;
    seen->ea = 0;
    seen->f = 0;
    seen->c = 0;
    *i = 0;
}

static int headers_is_complete(t_seen *s)
{
    return (s->no && s->so && s->we && s->ea && s->f && s->c);
}

static int dispatch_header_line(const char *line,
                                t_textures *tx, t_fc_colors *fc, t_seen *seen)
{
    int status;

    status = match_and_set_texture(line, "NO", &tx->no, &seen->no);
    if (status != 0)
      return status;
    status = match_and_set_texture(line, "SO", &tx->so, &seen->so);
    if (status != 0)
      return status;
    status = match_and_set_texture(line, "WE", &tx->we, &seen->we);
    if (status != 0)
      return status;
    status = match_and_set_texture(line, "EA", &tx->ea, &seen->ea);
    if (status != 0)
      return status;
    status = match_and_set_color(line, 'F', &fc->floor, &seen->f);
    if (status != 0)
      return status;
    status = match_and_set_color(line, 'C', &fc->ceiling, &seen->c);
    if (status != 0)
      return status;
    return 0;
}

static int find_starting_map(char **lines, int i)
{
    while (lines[i] && is_empty_line(lines[i]))
        i++;
    if (lines[i] == NULL)
        return -1;
    return i;
}

int parse_headers(char **lines, int *out_map_start, t_scene *scene)
{
    t_seen  seen;
    int     i;
    int     status;

    init_headers_state(&seen, &i);

    while (lines[i] && !headers_is_complete(&seen))
    {
        if (is_empty_line(lines[i])) { i++; continue; }

        status = dispatch_header_line(lines[i], &scene->textures, &scene->fc, &seen);
        if (status == -1) return (set_parse_error(scene, "Duplicate identifier"), 0);
        if (status ==  0) return (set_parse_error(scene, "Invalid identifier"), 0);
        i++;
    }
    if (!headers_is_complete(&seen))
        return (set_parse_error(scene, "Missing required elements (NO, SO, WE, EA, F, C)"), 0);

    i = find_starting_map(lines, i);
    if (i < 0)
        return (set_parse_error(scene, "No map found"), 0);

    *out_map_start = i;
    return 1;
}
