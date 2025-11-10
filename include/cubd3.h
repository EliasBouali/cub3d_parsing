#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>

#define READ_BUFFER 4096

typedef struct s_textures {
  char *no;
  char *so;
  char *we;
  char *ea;
} t_textures;

typedef struct s_color{
  int red;
  int green;
  int blue;
  int defined;
} t_color;

typedef struct s_fc_colors {
  t_color floor;
  t_color ceiling;
} t_fc_colors;

typedef struct s_seen {
  int no;
  int so;
  int we;
  int ea;
  int f;
  int c;
} t_seen;

typedef struct s_map
{
  char **lines_map;
  int rows;
  int cols;
} t_map;

typedef struct s_spawn
{
	int		found;
	int		row;
	int		col;
	char	dir;
}	t_spawn;

typedef struct s_scene {
  t_textures  textures;
  t_fc_colors fc;
  t_map       map;
  t_spawn     spawn;
  char *err;
} t_scene;

/* fonctions dans le dossier utils fichier utils.c: */
char    *ft_strrchr(const char *s, int c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strlen(const char *s);
void    *ft_memcpy(void *dst, const void *src, size_t n);
int     ft_isdigit(int c);

/* fonctions dans le dossier second_utils.c: */
int     is_space(char c);
void    skip_spaces(const char **cursor);
int     is_empty_line(const char *line);

/* fonction dans le dossier utils fichier parse_utils.c: */
void	init_scene_outputs(t_scene *scene);
void	free_textures(t_textures *textures);
void	free_map(t_map *map);
char	**load_lines(const char *path, t_scene *scene);
void	cleanup_scene(t_scene *scene);

/* fonction dans le dossier utils fichier second_parse_utils.c: */
int	finish_map(t_scene *scene);
int	parse_headers_and_map(char **lines, t_scene *scene, int *map_start);
int	scan_and_set_spawn(t_scene *scene);

/* fonction dans le dossier src/file/file_validation.c: */
int open_check(const char *path, t_scene *scene);

/* fonction dans le dossier src/file/read_file.c: */
char	*read_file(int fd, t_scene *scene);

/* fonction dans le dossier src/file/split_lines.c: */
char **split_lines(const char *filebuf, t_scene *scene);

/* fonctions dans le dossier src/parse/parse_headers.c: */
int	parse_headers(char **lines, int *out_map_start, t_scene *scene);

/* fonctions dans le dossier src/parse/parse_headers_textures.c: */
int     match_texture_line(const char *line, const char *ident, char **out_path);

/* fonctions dans le dossier src/parse/parse_headers_colors.c: */
int     match_color_line(const char *line, char id, t_color *out);

/* fonctions dans le dossier src/parse/parse_headers_assign.c: */
int     match_and_set_texture(const char *line, const char *id,
                              char **slot, int *seen_flag);
int     match_and_set_color(const char *line, char id,
                            t_color *slot, int *seen_flag);

/* fonction dans le dossier src/parse/parse_validate_textures.c: */
int     validate_textures_exist(t_textures *tx);

/* fonction dans le dossier src/parse/parse_map_block.c: */
int	parse_map_block(char **lines, int map_start, t_map *out, t_scene *scene);

/* fonction dans le dossier src/parse/parse_spawn.c: */
int	scan_map_for_spawn(t_scene *scene);

/* fonction dans le dossier src/parse/parse_map_rectangle.c: */
int     make_map_rectangular(t_map *map);

/* fonction dans le dossier src/parse/parse_check_map_closed.c: */
int     check_map_closed(t_map *map);

/* fonction dans le dossier src/parse/parse_validate_textures.c: */
int validate_textures_exist(t_textures *tx);

/* fonction dans le dossier src/parse/parse.c :*/
int	parse_scene(const char *path, t_scene *scene);

/* fonction dans le dossier src/parse/parse_error.c: */
void set_parse_error(t_scene *scene, const char *msg);
const char *get_parse_error(const t_scene *scene);

#endif
