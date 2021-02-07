#include "../cub3d.h"

t_game new_game() {
    t_game game;
    // size
    game.size.width = 0;
    game.size.height = 0;

    game.map.spawn.y = -1;
    game.map.spawn.x = -1;

    game.render.ray.dirX = -1;
    game.render.ray.dirY = 0;

    game.render.ray.planeX = 0;
    game.render.ray.planeY = 0.66;

    game.render.ray.oldTime = 0;
    game.render.ray.time = 0;


    game.texture.ea = NULL;
    game.texture.we = NULL;
    game.texture.so = NULL;
    game.texture.no = NULL;

    game.box.c_sky = NULL;
    game.box.c_floor = NULL;
    game.box.c_sprite = NULL;

    return (game);
}

void destroy_map(t_game *game) {
    free(game->texture.ea);
    free(game->texture.we);
    free(game->texture.so);
    free(game->texture.no);

    free(game->box.c_floor);
    free(game->box.c_sky);
    free(game->box.c_sprite);
}