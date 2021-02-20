#include "../../cub3d.h"

void rayDir(t_game *game, int mapX, int mapY) {
    if(game->render.ray.rayDirX < 0)
    {
        game->render.ray.stepX = -1;
        game->render.ray.sideDistX = (double)(game->map.spawn.x - mapX) *  game->render.ray.deltaDistX;
    }
    else
    {
        game->render.ray.stepX = 1;
        game->render.ray.sideDistX = (double)(mapX + 1 - game->map.spawn.x) *  game->render.ray.deltaDistX;
    }
    if(game->render.ray.rayDirY < 0)
    {
        game->render.ray.stepY = -1;
        game->render.ray.sideDistY = (double)(game->map.spawn.y - mapY) *  game->render.ray.deltaDistY;
    }
    else
    {
        game->render.ray.stepY = 1;
        game->render.ray.sideDistY = (double)(mapY + 1 - game->map.spawn.y) * game->render.ray.deltaDistY;
    }
}


void set_start_ray(int x, t_game *game) {
    //calculate ray position and direction
    game->render.ray.angleX = 2 * x / (double)game->size.width - 1; //x-coordinate in camera space
    game->render.ray.rayDirX = game->render.ray.dirX + game->render.ray.planeX * game->render.ray.angleX;
    game->render.ray.rayDirY = game->render.ray.dirY + game->render.ray.planeY * game->render.ray.angleX;
    //which box of the map we're in
    game->render.ray.mapX = (int)game->map.spawn.x;
    game->render.ray.mapY = (int)game->map.spawn.y;

    game->render.ray.deltaDistX = fabs(1 / game->render.ray.rayDirX);
    game->render.ray.deltaDistY = fabs(1 / game->render.ray.rayDirY);
}


void dda(t_game *game, int *side) {
    int hit;

    hit = 0;
    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(game->render.ray.sideDistX < game->render.ray.sideDistY)
        {
            game->render.ray.sideDistX += game->render.ray.deltaDistX;
            game->render.ray.mapX += game->render.ray.stepX;
            *side = 0;
        }
        else
        {
            game->render.ray.sideDistY += game->render.ray.deltaDistY;
            game->render.ray.mapY += game->render.ray.stepY;
            *side = 1;
        }
        //Check if ray has hit a wall
        if(game->map.tmap[game->render.ray.mapX][game->render.ray.mapY] == '1')
            hit = 1;
    }
}

void lineHeight(t_game *game) {
     //Calculate height of line to draw on screen
    game->render.ray.lineHeight = (int)(game->size.height / game->render.ray.perpWallDist);
    //calculate lowest and highest pixel to fill in current stripe
    game->render.ray.drawStart = -game->render.ray.lineHeight / 2 + game->size.height / 2;
    if(game->render.ray.drawStart < 0) {
        game->render.ray.drawStart = 0;
    }
    game->render.ray.drawEnd = game->render.ray.lineHeight / 2 + game->size.height / 2;
    if(game->render.ray.drawEnd >= game->size.height) {
        game->render.ray.drawEnd = game->size.height - 1;
    }
}