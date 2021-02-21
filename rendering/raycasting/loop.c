#include "../../cub3d.h"



int rendering(t_game *game) {
    int side;
    int x;

    move(game);
    x = 0;
    while(x < game->size.width)
    {
        set_start_ray(x, game);
        rayDir(game, game->render.ray.mapX, game->render.ray.mapY);
        dda(game, &side);
        if(side == 0)
            game->render.ray.perpWallDist = (game->render.ray.mapX - game->map.spawn.x + (1 - game->render.ray.stepX) / 2) / game->render.ray.rayDirX;
        else
            game->render.ray.perpWallDist = (game->render.ray.mapY - game->map.spawn.y + (1 - game->render.ray.stepY) / 2) / game->render.ray.rayDirY;
        lineHeight(game);
        wall_casting(game, side, x);
        game->render.ray.zbuf[x] = game->render.ray.perpWallDist; 
        x++;
    }
    sprite_casting(game);

    if(game->settings.bmp_required == 1)
        file_bmp(game);

    mlx_put_image_to_window(game->render.mlx, game->render.win, game->render.frame.img, 0, 0);
    return (1);
}
