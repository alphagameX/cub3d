#include "../../cub3d.h"

double width_wall(t_game *game, int side) {
    double wallX; 
    if (side == 0) {
        wallX = game->map.spawn.y + game->render.ray.perpWallDist * game->render.ray.rayDirY;
    } else {
        wallX = game->map.spawn.x + game->render.ray.perpWallDist * game->render.ray.rayDirX;
    }
    wallX -= floor(wallX);
    return (wallX);
}

int width_tex(t_game *game, double wallX, int side) {
    int texX = (int)(wallX * (double)game->texture.we.tex.width);
    // get text height
    if(side == 0 && game->render.ray.rayDirX > 0) {
        texX = game->texture.we.tex.width - texX - 1;
    }
    if(side == 1 && game->render.ray.rayDirY < 0) {
        texX = game->texture.we.tex.width - texX - 1;
    }
    return (texX);
}

char *select_texture(t_game *game, int side, int texY, int texX) {
    if(side == 0 && game->render.ray.rayDirX < 0)
        return get_color(&game->texture.no.tex.addr, game->texture.no.tex.width, texY, texX);
    else if(side == 0 && game->render.ray.rayDirX > 0)
        return get_color(&game->texture.so.tex.addr, game->texture.so.tex.width, texY, texX);
    else if(side == 1 && game->render.ray.rayDirY < 0)
        return get_color(&game->texture.we.tex.addr, game->texture.we.tex.width, texY, texX);
    else if(side == 1 && game->render.ray.rayDirY > 0)
        return get_color(&game->texture.ea.tex.addr, game->texture.ea.tex.width, texY, texX);
    return (NULL);
}

void wall_casting(t_game *game, int side, int x) {
    int y;
    double wallX;
    int texX;
    int texY;
    double texPos;
       
    wallX = width_wall(game, side);
    texX = width_tex(game, wallX, side);
    texPos = (game->render.ray.drawStart - game->size.height / 2 + game->render.ray.lineHeight / 2) * (1.0 * game->texture.we.tex.height / game->render.ray.lineHeight);
    y = 0;
    while(y < game->size.height) {
        if(y < game->render.ray.drawStart) {
            my_mlx_pixel_put(&game->render.frame, x, y, game->box.floor.color);
        } else if(y >= game->render.ray.drawStart && y <= game->render.ray.drawEnd) {
            texY = (int)texPos & (game->texture.we.tex.width - 1);
            texPos += 1.0 * game->texture.we.tex.height / game->render.ray.lineHeight;
            my_mlx_pixel_put(&game->render.frame, x, y, *(unsigned int*)select_texture(game, side, texY, texX));
        } else if(y > game->render.ray.drawEnd) {
            my_mlx_pixel_put(&game->render.frame, x, y, game->box.sky.color);
        }
        y++;
    }
}