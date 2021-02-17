#include "../parsing.h"

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

    if(is_already_add(&game->box.c_sprite, x, y) == 0) {
         if(!(new = (t_scoord *)malloc(sizeof(t_scoord) * game->box.c_sprite.nb_sprite + 1)))
            destroy_game(game);
        while(i < game->box.c_sprite.nb_sprite) {
            new[i].x = game->box.c_sprite.data[i].x;
            new[i].y = game->box.c_sprite.data[i].y;
            i++;
        }

        new[i].x = x;
        new[i].y = y;

        i = 0;
        while(i > 0 && i < game->box.c_sprite.nb_sprite)
            free(game->box.c_sprite.data);
        
        game->box.c_sprite.nb_sprite++;
        game->box.c_sprite.data = new;
    }

    //exit(0);
}