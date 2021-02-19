#include "../cub3d.h"

void forward(t_game *game, double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x + game->render.ray.dirX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y + game->render.ray.dirY * colision)];
    if(x != '1' && x != '2')
        game->map.spawn.x += game->render.ray.dirX * 0.2;
    if(y != '1' && y != '2')
        game->map.spawn.y += game->render.ray.dirY * 0.2;
}

void backward(t_game *game,  double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x - game->render.ray.dirX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y - game->render.ray.dirY * 0.1)];
    if(x != '1' && x != '2')
        game->map.spawn.x -= game->render.ray.dirX * 0.2;
    if(y != '1' && y != '2')
        game->map.spawn.y -= game->render.ray.dirY * 0.2;
}

void strate_left(t_game *game, double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x + game->render.ray.planeX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y + game->render.ray.planeY * colision)];
    if(x != '1' && x != '2')
        game->map.spawn.x += game->render.ray.planeX * 0.2;
    if(y != '1' && y != '2')
        game->map.spawn.y += game->render.ray.planeY * 0.2;
}

void strate_right(t_game *game, double colision) {
    char x;
    char y;

    x = game->map.tmap[(int)(game->map.spawn.x - game->render.ray.planeX * colision)][(int)game->map.spawn.y];
    y = game->map.tmap[(int)game->map.spawn.x][(int)(game->map.spawn.y - game->render.ray.planeY * colision)];
    if(x != '1' && x != '2')
        game->map.spawn.x -= game->render.ray.planeX * 0.2;
    if(y != '1' && y != '2')
        game->map.spawn.y -= game->render.ray.planeY * 0.2;
}
