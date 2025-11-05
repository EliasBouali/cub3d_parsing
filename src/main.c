// main de chatgpt:
#include "cubd3.h"

/* libère le tableau retourné par split_lines() */
static void free_lines(char **lines)
{
    int i = 0;
    if (!lines) return;
    while (lines[i]) { free(lines[i]); i++; }
    free(lines);
}

/* libère les chemins textures si définis */
static void free_textures(t_textures *tx)
{
    if (!tx) return;
    free(tx->no);
    free(tx->so);
    free(tx->we);
    free(tx->ea);
}

/* libère la map extraite par parse_map_block() */
static void free_map(t_map *m)
{
    int i = 0;
    if (!m || !m->lines_map) return;
    while (i < m->rows) { free(m->lines_map[i]); i++; }
    free(m->lines_map);
}

int main(int argc, char **argv)
{
    int         fd;
    char       *buf;
    char      **lines;
    int         map_start;
    t_textures  tx;
    t_fc_colors fc;
    t_map       m;

    if (argc != 2) return 1;

    fd = open_check(argv[1]);                 /* fd ou -1 */
    if (fd < 0) return 1;

    buf = read_file(fd);                      /* buffer alloué */
    close(fd);
    if (!buf) return 1;

    lines = split_lines(buf);                 /* tableau de lignes (NULL-terminé) */
    free(buf);
    if (!lines) return 1;

    /* parse des headers → remplit tx/fc et positionne map_start */
    if (!parse_headers(lines, &map_start, &tx, &fc))
    {
        /* parse_headers a déjà affiché l'erreur */
        free_textures(&tx);
        free_lines(lines);
        return 1;
    }

    /* extraction du bloc map brut (espaces conservés) */
    if (!parse_map_block(lines, map_start, &m))
    {
        /* parse_map_block a déjà affiché l'erreur */
        free_textures(&tx);
        free_lines(lines);
        return 1;
    }

    /* sortie minimale pour vérifier le début du parsing */
    printf("OK %d %d\n", map_start, m.rows);

    /* nettoyage */
    free_map(&m);
    free_textures(&tx);
    free_lines(lines);
    return 0;
}
