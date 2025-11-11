#include "cubd3.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
    {
        printf("Error\nUsage: %s <file.cub>\n", argv[0]);
        return (1);
    }
    if (!parse_scene(argv[1], &scene))
    {
        printf("Error\n%s\n", get_parse_error(&scene));
        cleanup_scene(&scene);
        return (1);
    }

    /* --- Succès : logs utiles pendant le dev (peuvent être retirés) --- */
    printf("OK spawn=(%d,%d,%c) rows=%d cols=%d\n",
           scene.spawn.row, scene.spawn.col, scene.spawn.dir,
           scene.map.rows, scene.map.cols);

    /* Pour afficher la map rectangulaire pendant tes tests, décommente :
    {
        int r = 0;
        while (r < scene.map.rows)
        {
            printf("%s\n", scene.map.lines_map[r]);
            r++;
        }
    }
    */

    cleanup_scene(&scene);
    return (0);
}

