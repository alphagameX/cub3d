#include "../parsing.h"

void init_moves(t_move *moves) {
    int i = 0;
    moves->nb_move = 0;
    while(i < 10) {
        moves->wait_mode[i] = -1;
        i++;
    }
}

void set_dir(t_game *game) {

    if(game->map.spawn.dir == 'N') {
        game->render.ray.dirX = -1;
        game->render.ray.dirY = 0;
        game->render.ray.planeX = 0;
        game->render.ray.planeY = 0.66;
    }

     if(game->map.spawn.dir == 'E') {
        game->render.ray.dirX = 0;
        game->render.ray.dirY = -1;
        game->render.ray.planeX = -0.66;
        game->render.ray.planeY = 0;
    }

     if(game->map.spawn.dir == 'S') {
        game->render.ray.dirX = 1;
        game->render.ray.dirY = 0;
        game->render.ray.planeX = 0;
        game->render.ray.planeY = -0.66;
    }

     if(game->map.spawn.dir == 'W') {
        game->render.ray.dirX = 0;
        game->render.ray.dirY = 1;
        game->render.ray.planeX = 0.66;
        game->render.ray.planeY = 0;
    }
}

void init_texture(t_texture *texture) {
    texture->ea.path = NULL;
    texture->no.path = NULL;
    texture->so.path = NULL;
    texture->we.path = NULL;

    texture->ea.is_see = 0;
    texture->no.is_see = 0;
    texture->so.is_see = 0;
    texture->we.is_see = 0;
}

t_game new_game() {
    t_game game;
    // size

    init_texture(&game.texture);

    game.size.width = 0;
    game.size.height = 0;

    game.map.height = 0;
    game.map.width = 0;

    game.map.spawn.y = -1;
    game.map.spawn.x = -1;

    init_moves(&game.render.moves);
    init_texture(&game.texture);

    game.box.c_sprite.path = NULL;
    game.box.floor.is_see = 0;
    game.box.sky.is_see = 0;

    return (game);
}

void destroy_game(t_game *game) {
    int i;

    i = 0;
    if(game->texture.ea.path)
        free(game->texture.ea.path);
    if(game->texture.we.path)
        free(game->texture.we.path);
    if(game->texture.so.path)
        free(game->texture.so.path);
    if(game->texture.no.path)
        free(game->texture.no.path);

    if(game->box.c_sprite.path)
        free(game->box.c_sprite.path);

    if(game->map.height != 0 && game->map.width != 0) {
        while(game->map.tmap[i]) {
            free(game->map.tmap[i]);
            i++;
        }
    }

    exit(0);
}