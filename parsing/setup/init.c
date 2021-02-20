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

     if(game->map.spawn.dir == 'W') {
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

     if(game->map.spawn.dir == 'E') {
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

    texture->ea.tex.img = NULL;
    texture->no.tex.img = NULL;
    texture->so.tex.img = NULL;
    texture->we.tex.img = NULL;

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
    game.size.is_see = 0;

    game.settings.move_speed = 0.1;
    game.settings.hit_distance = 0.3;
    game.settings.rot_speed = 0.1;

    game.map.height = 0;
    game.map.width = 0;

    game.map.spawn.y = -1;
    game.map.spawn.x = -1;

    init_moves(&game.render.moves);
    init_texture(&game.texture);

    game.render.ray.zbuf = NULL;
    game.render.mlx = NULL;
    game.render.win = NULL;

    game.box.sprite.path = NULL;
    game.box.sprite.data = NULL;
    game.box.sprite.frame.img = NULL;
    game.box.sprite.nb_sprite = 0;
    game.box.sprite.is_see = 0;
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

    if(game->box.sprite.path)
        free(game->box.sprite.path);

    if(game->box.sprite.nb_sprite > 0)
        free(game->box.sprite.data);

    if(game->map.height != 0 && game->map.width != 0) {
        while(game->map.tmap[i]) {
            free(game->map.tmap[i]);
            i++;
        }
        free(game->map.tmap);
    }

    if(game->texture.ea.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.ea.tex.img);
    if(game->texture.no.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.no.tex.img);
    if(game->texture.we.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.we.tex.img);
    if(game->texture.so.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.so.tex.img);
    if(game->box.sprite.frame.img != NULL)
        mlx_destroy_image(game->render.mlx, game->box.sprite.frame.img);
    if(game->render.win != NULL)
        mlx_destroy_window(game->render.mlx, game->render.win);

    free(game->render.ray.zbuf);

    //mlx_destroy_display(game->render.mlx);

    //system("leaks cub3d");

    exit(0);
}

