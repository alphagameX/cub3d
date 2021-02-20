#include "../../cub3d.h"

void forward(t_game *game, double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x + game->render.ray.dirX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y + game->render.ray.dirY * colision)];
    if(x != '1' && x != '2')
        game->map.spawn.x += game->render.ray.dirX * game->settings.move_speed;
    if(y != '1' && y != '2')
        game->map.spawn.y += game->render.ray.dirY * game->settings.move_speed;
}

void backward(t_game *game,  double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x - game->render.ray.dirX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y - game->render.ray.dirY * 0.1)];
    if(x != '1' && x != '2')
        game->map.spawn.x -= game->render.ray.dirX * game->settings.move_speed;
    if(y != '1' && y != '2')
        game->map.spawn.y -= game->render.ray.dirY * game->settings.move_speed;
}

void strate_left(t_game *game, double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x + game->render.ray.planeX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y + game->render.ray.planeY * colision)];
    if(x != '1' && x != '2')
        game->map.spawn.x += game->render.ray.planeX * game->settings.move_speed;
    if(y != '1' && y != '2')
        game->map.spawn.y += game->render.ray.planeY * game->settings.move_speed;
}

void strate_right(t_game *game, double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x - game->render.ray.planeX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y - game->render.ray.planeY * colision)];
    if(x != '1' && x != '2')
        game->map.spawn.x -= game->render.ray.planeX * game->settings.move_speed;
    if(y != '1' && y != '2')
        game->map.spawn.y -= game->render.ray.planeY * game->settings.move_speed;
}

int move(t_game *game) {
    int i;

    i = 0;
    while(i < game->render.moves.nb_move && game->render.moves.wait_mode[i] != -1) {
        if(game->render.moves.wait_mode[i] == UP)
           forward(game, game->settings.hit_distance);
        if(game->render.moves.wait_mode[i] == DOWN)
            backward(game, game->settings.hit_distance);
        if(game->render.moves.wait_mode[i] == LEFT)
           strate_left(game, game->settings.hit_distance);
        if(game->render.moves.wait_mode[i] == RIGHT)
           strate_right(game, game->settings.hit_distance);
        if(game->render.moves.wait_mode[i] == TURN_LEFT)
          turn_left(game, game->settings.rot_speed);
        if (game->render.moves.wait_mode[i] == TURN_RIGHT)
          turn_right(game, game->settings.rot_speed);
        if(game->render.moves.wait_mode[i] == ECHAP)
            destroy_game(game);
        i++;
    }

    return (1);
}
