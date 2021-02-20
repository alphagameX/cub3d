#include "../../parsing.h"

int relative_distance(t_spawn p, t_scoord s) {
    double x = s.x;
    double y = s.y;

    return ((int)fabs(fabs(p.x - p.y) - fabs(x - y)));
}

void swap_sprite(t_scoord *src, t_scoord *dst) {
    t_scoord tmp;

    tmp.x = src->x;
    tmp.y = src->y;

    src->x = dst->x;
    src->y = dst->y;

    dst->x = tmp.x;
    dst->y = tmp.y;
}

void sortSprite(t_sprite *sprite, t_spawn spawn) {
    int i = 0;
    int e;

    while(i < sprite->nb_sprite) {
        e = i + 1;
        while(e < sprite->nb_sprite) {
            if(relative_distance(spawn, sprite->data[i]) < relative_distance(spawn, sprite->data[e])) {
                swap_sprite(&sprite->data[i], &sprite->data[e]);
            }
            e++;
        }
        i++;
    }
}