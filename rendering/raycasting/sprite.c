#include "../../cub3d.h"

double sprite(char d, t_game *game, int e) {
    if(d == 'X')
        return (game->box.sprite.data[e].y - game->map.spawn.x);
    if(d == 'Y')
        return (game->box.sprite.data[e].x - game->map.spawn.y);
    destroy_game(game);
    return(0);
}

double transform(char d, t_game *game, int e) {
    if(d == 'X')
        return (game->box.sprite.invDet * (game->render.ray.dirY * sprite('X', game, e) - game->render.ray.dirX * sprite('Y', game, e)));
    if(d == 'Y')
        return (game->box.sprite.invDet * (-game->render.ray.planeY * sprite('X', game, e) + game->render.ray.planeX * sprite('Y', game, e)));
    destroy_game(game);
    return(0);
}


void set_start_sprite_ray(t_game *game, int e) {
    game->box.sprite.invDet = 1.0 / (game->render.ray.planeX * game->render.ray.dirY - game->render.ray.dirX * game->render.ray.planeY); 
    game->box.sprite.spriteScreenX = (int)((game->size.width / 2) * (1 + transform('X', game, e) / transform('Y', game, e)));
    game->box.sprite.spriteHeight = abs((int)(game->size.height / (transform('Y', game, e))));
    game->box.sprite.spriteWidth = abs( (int) (game->size.height / (transform('Y', game, e))));
    game->box.sprite.drawStartY = -game->box.sprite.spriteHeight / 2 + game->size.height / 2;
    game->box.sprite.drawEndY = game->box.sprite.spriteHeight / 2 + game->size.height / 2;
    game->box.sprite.drawStartX = -game->box.sprite.spriteWidth / 2 + game->box.sprite.spriteScreenX;
    game->box.sprite.drawEndX = game->box.sprite.spriteWidth / 2 + game->box.sprite.spriteScreenX;
    if(game->box.sprite.drawStartY < 0)
        game->box.sprite.drawStartY = 0;
    if(game->box.sprite.drawEndY >= game->size.height)
        game->box.sprite.drawEndY = game->size.height - 1;
    if(game->box.sprite.drawStartX < 0) 
        game->box.sprite.drawStartX = 0;
    if(game->box.sprite.drawEndX >= game->size.width)
        game->box.sprite.drawEndX = game->size.width - 1;
}

void drawSprite(t_game *game, int e) {
    int texX;
    int texY;
    char *color;

    for(int stripe = game->box.sprite.drawStartX; stripe < game->box.sprite.drawEndX; stripe++)
    {
        texX = (int)(256 * (stripe - (-game->box.sprite.spriteWidth / 2 + game->box.sprite.spriteScreenX)) * game->box.sprite.frame.width / game->box.sprite.spriteWidth) / 256;
        if(transform('Y', game, e) > 0 && stripe > 0 && stripe < game->size.width && transform('Y', game, e) < game->render.ray.zbuf[stripe])
        for(int y = game->box.sprite.drawStartY; y < game->box.sprite.drawEndY; y++)
        {
            int d = (y) * 256 - game->size.height * 128 + game->box.sprite.spriteHeight * 128;
            texY = ((d * game->box.sprite.frame.height) / game->box.sprite.spriteHeight) / 256;
            color = get_color(&game->box.sprite.frame.addr, game->box.sprite.frame.width, texY, texX);
            if((*(unsigned int *)color & 0x00FFFFFF) != 0) {
                my_mlx_pixel_put(&game->render.frame, stripe, y, *(unsigned int *)color);
            }
        }
    }
}

void sprite_casting(t_game *game) {
    int e = 0;
    
    while(e < game->box.sprite.nb_sprite) {
        sortSprite(&game->box.sprite, game->map.spawn);
        set_start_sprite_ray(game, e);
        drawSprite(game, e);
        e++;
    }
}