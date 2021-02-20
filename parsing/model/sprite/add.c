#include "../../parsing.h"

int is_already_add(t_sprite *sprite, int x, int y) {
    int i ;

    i = 0;
    while(i < sprite->nb_sprite) {
        if(sprite->data[i].y == y && sprite->data[i].x == x)
            return (1);
        i++; 
    }
    return (0);
}

void push_sprite(t_game *game, int x, int y) {

    t_scoord s;
    t_scoord *new;
    int i;

    s.x = x;
    s.y = y;
    i = 0;

    if(is_already_add(&game->box.sprite, x, y) == 0) {
         if(!(new = malloc(sizeof(t_scoord) * (game->box.sprite.nb_sprite + 1))))
            destroy_game(game);
        while(i < game->box.sprite.nb_sprite) {
            new[i].x = game->box.sprite.data[i].x;
            new[i].y = game->box.sprite.data[i].y;
            i++;
        }
        new[i].x = x + 0.5;
        new[i].y = y + 0.5;

        if(game->box.sprite.nb_sprite > 0)
            free(game->box.sprite.data);
        game->box.sprite.nb_sprite++;
        game->box.sprite.data = new;
    }
}

