#include "../../cub3d.h"

void turn_left(t_game *game, double rot_speed) {
    double oldDirX; 
    double oldPlaneX;

    oldDirX = game->render.ray.dirX;
    oldPlaneX = game->render.ray.planeX;
    game->render.ray.dirX = game->render.ray.dirX * cos(-rot_speed) - game->render.ray.dirY * sin(-rot_speed);
    game->render.ray.dirY = oldDirX * sin(-rot_speed) + game->render.ray.dirY * cos(-rot_speed);
    game->render.ray.planeX = game->render.ray.planeX * cos(-rot_speed) - game->render.ray.planeY * sin(-rot_speed);
    game->render.ray.planeY = oldPlaneX * sin(-rot_speed) + game->render.ray.planeY * cos(-rot_speed);
}
void turn_right(t_game *game, double rot_speed) {
    double oldDirX; 
    double oldPlaneX; 

    oldDirX = game->render.ray.dirX;
    oldPlaneX= game->render.ray.planeX;
    game->render.ray.dirX = game->render.ray.dirX * cos(rot_speed) - game->render.ray.dirY * sin(rot_speed);
    game->render.ray.dirY = oldDirX * sin(rot_speed) + game->render.ray.dirY * cos(rot_speed);
    game->render.ray.planeX = game->render.ray.planeX * cos(rot_speed) - game->render.ray.planeY * sin(rot_speed);
    game->render.ray.planeY = oldPlaneX * sin(rot_speed) + game->render.ray.planeY * cos(rot_speed);
}