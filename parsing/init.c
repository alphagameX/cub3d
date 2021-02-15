#include "../cub3d.h"

void init_moves(t_move *moves) {
    int i = 0;
    moves->nb_move = 0;
    while(i < 10) {
        moves->wait_mode[i] = -1;
        i++;
    }
}

t_game new_game() {
    t_game game;
    // size
    game.size.width = 0;
    game.size.height = 0;

    game.map.height = 0;
    game.map.width = 0;

    game.map.spawn.y = -1;
    game.map.spawn.x = -1;

    game.render.ray.dirX = -1;
    game.render.ray.dirY = 0;

    game.render.ray.planeX = 0;
    game.render.ray.planeY = 0.66;

    init_moves(&game.render.moves);

    game.texture.ea.path = NULL;
    game.texture.we.path = NULL;
    game.texture.so.path = NULL;
    game.texture.no.path = NULL;

    game.box.c_sky = NULL;
    game.box.c_floor = NULL;
    game.box.c_sprite = NULL;

    return (game);
}

void destroy_map(t_game *game) {
    int i;

    i = 0;
    free(game->texture.ea.path);
    free(game->texture.we.path);
    free(game->texture.so.path);
    free(game->texture.no.path);
    free(game->box.c_floor);
    free(game->box.c_sky);
    free(game->box.c_sprite);

    while(game->map.tmap[i]) {
        free(game->map.tmap[i]);
        i++;
    }
}