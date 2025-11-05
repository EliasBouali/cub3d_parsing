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



// fonctions dans le dossier utils fichier utils:
char    *ft_strrchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
size_t  ft_strlen(const char *s);
void    *ft_memcpy(void *dst, const void *src, size_t n);
int ft_isdigit(int c);

// fonction dans le dossier second_utils.c:
int is_space(char c);
void skip_spaces(const char **cursor);
int is_empty_line(const char *line);

// fonction dans le dossier src/file fichier file_validations.c:
int open_check(const char *path);

// fonction dans le dossier src/file/read_file.c:
char *read_file(int fd);

// fonction dans le dossier src/file/split_lines.c:
char **split_lines(const char *filebuf);

// fonction dans le dossier src/parse/parse_headers.c:
int parse_headers(char **lines, int *out_map_start,
                  t_textures *wall_textures, t_fc_colors *floor_ceiling);

// fonction dans le dossier src/parse/parse_map_block.c:
int parse_map_block(char **lines, int map_start, t_map *out);


#endif
