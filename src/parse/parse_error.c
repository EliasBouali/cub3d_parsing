#include "cubd3.h"

void set_parse_error(t_scene *scene, const char *msg)
{
    size_t len;

    if (!scene)
        return;
    if (scene->err)
    {
      free(scene->err);
      scene->err = NULL;
    }
    if (!msg || !*msg)
        msg = "Unknown parse error";
    len = strlen(msg);
    scene->err = (char *)malloc(len + 1);
    if (scene->err)
        memcpy(scene->err, msg, len + 1);
}

const char *get_parse_error(const t_scene *scene)
{
    if (!scene || !scene->err)
        return "Unknown parse error";
    return scene->err;
}
