#include "../cub3d.h"

int relative_distance(t_spawn p, t_scoord s) {
    double x = s.x;
    double y = s.y;

    return ((int)fabs(fabs(p.x - p.y) - fabs(x - y)));
}

void swap_sprite(t_scoord *src, t_scoord *dst) {
    t_scoord tmp;

    tmp.x = src->x;
    tmp.y = src->y;

    src->x = dst->x;
    src->y = dst->y;

    dst->x = tmp.x;
    dst->y = tmp.y;
}

void sortSprite(t_sprite *sprite, t_spawn spawn) {
    int i = 0;
    int e;
    t_scoord tmp;

    double posX = spawn.x;
    double posY = spawn.y;

    while(i < sprite->nb_sprite) {
        e = i + 1;
        while(e < sprite->nb_sprite) {
            if(relative_distance(spawn, sprite->data[i]) < relative_distance(spawn, sprite->data[e])) {
                swap_sprite(&sprite->data[i], &sprite->data[e]);
            }
            e++;
        }
        i++;
    }
}

int move(t_game *game) {
    int i;

    i = 0;
    while(i < game->render.moves.nb_move && game->render.moves.wait_mode[i] != -1) {
        if(game->render.moves.wait_mode[i] == UP)
           forward(game, HIT_DIST);
        if(game->render.moves.wait_mode[i] == DOWN)
            backward(game, HIT_DIST);
        if(game->render.moves.wait_mode[i] == LEFT)
           strate_left(game, HIT_DIST);
        if(game->render.moves.wait_mode[i] == RIGHT)
           strate_right(game, HIT_DIST);
        if(game->render.moves.wait_mode[i] == TURN_LEFT)
          turn_left(game, ROT_SPEED);
        if (game->render.moves.wait_mode[i] == TURN_RIGHT)
          turn_right(game, ROT_SPEED);
        if(game->render.moves.wait_mode[i] == ECHAP)
            destroy_game(game);
        i++;
    }

    return (1);
}

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
            if(game->map.tmap[game->render.ray.mapX][game->render.ray.mapY] == '1') {
                hit = 1;
            }
        }
}

int rendering(t_game *game) {
    int side;
    int x;

    new_image(game);
    move(game);
    x = 0;
    while(x < game->size.width)
    {
        set_start_ray(x, game);
        rayDir(game, game->render.ray.mapX, game->render.ray.mapY);
        dda(game, &side);
        //perform DDA
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if(side == 0)
            game->render.ray.perpWallDist = (game->render.ray.mapX - game->map.spawn.x + (1 - game->render.ray.stepX) / 2) / game->render.ray.rayDirX;
        else
            game->render.ray.perpWallDist = (game->render.ray.mapY - game->map.spawn.y + (1 - game->render.ray.stepY) / 2) / game->render.ray.rayDirY;


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


        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (side == 0) {
            wallX = game->map.spawn.y + game->render.ray.perpWallDist * game->render.ray.rayDirY;
        } else {
            wallX = game->map.spawn.x + game->render.ray.perpWallDist * game->render.ray.rayDirX;
        }
        wallX -= floor(wallX);


        int texX = (int)(wallX * (double)game->texture.we.tex.width);
        // get text height
        if(side == 0 && game->render.ray.rayDirX > 0) {
            texX = game->texture.we.tex.width - texX - 1;
        }
        if(side == 1 && game->render.ray.rayDirY < 0) {
            texX = game->texture.we.tex.width - texX - 1;
        }

        double step = 1.0 * game->texture.we.tex.height / game->render.ray.lineHeight;


        // Starting texture coordinate
        double texPos = (game->render.ray.drawStart - game->size.height / 2 + game->render.ray.lineHeight / 2) * step;

        int y = 0;
        while(y < game->size.height) {
            if(y < game->render.ray.drawStart) {
                my_mlx_pixel_put(&game->render.frame, x, y, game->box.floor.color);
            } else if(y >= game->render.ray.drawStart && y <= game->render.ray.drawEnd) {
                int texY = (int)texPos & (game->texture.we.tex.width - 1);
                texPos += step;
                char *color;
                if(side == 0 && game->render.ray.rayDirX < 0)
                    color = game->texture.no.tex.addr + (4 * game->texture.no.tex.width * texY) + (4 * texX);
                else if(side == 0 && game->render.ray.rayDirX > 0)
                    color = game->texture.so.tex.addr + (4 * game->texture.so.tex.width * texY) + (4 * texX);
                else if(side == 1 && game->render.ray.rayDirY < 0)
                    color = game->texture.we.tex.addr + (4 * game->texture.we.tex.width * texY) + (4 * texX);
                else if(side == 1 && game->render.ray.rayDirY > 0)
                    color = game->texture.ea.tex.addr + (4 * game->texture.ea.tex.width * texY) + (4 * texX);

                my_mlx_pixel_put(&game->render.frame, x, y, *(unsigned int *)color);
            } else if(y > game->render.ray.drawEnd) {
                my_mlx_pixel_put(&game->render.frame, x, y, game->box.sky.color);
            }
            y++;
        }

        game->render.ray.zbuf[x] = game->render.ray.perpWallDist; 
        x++;
    }



    int e = 0;

    while(e < game->box.c_sprite.nb_sprite) {
        sortSprite(&game->box.c_sprite, game->map.spawn);
        double spriteX = game->box.c_sprite.data[e].y - game->map.spawn.x;
        double spriteY = game->box.c_sprite.data[e].x - game->map.spawn.y;
        double invDet = 1.0 / (game->render.ray.planeX * game->render.ray.dirY - game->render.ray.dirX * game->render.ray.planeY); 
        double transformX = invDet * (game->render.ray.dirY * spriteX - game->render.ray.dirX * spriteY);
        double transformY = invDet * (-game->render.ray.planeY * spriteX + game->render.ray.planeX * spriteY);
        int spriteScreenX = (int)((game->size.width / 2) * (1 + transformX / transformY));
        int spriteHeight = abs((int)(game->size.height / (transformY)));
        int drawStartY = -spriteHeight / 2 + game->size.height / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + game->size.height / 2;
        if(drawEndY >= game->size.height) drawEndY = game->size.height - 1;
        int spriteWidth = abs( (int) (game->size.height / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= game->size.width) drawEndX = game->size.width - 1;

        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * game->box.c_sprite.frame.width / spriteWidth) / 256;
            if(transformY > 0 && stripe > 0 && stripe < game->size.width && transformY < game->render.ray.zbuf[stripe])
            for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
            {
                int d = (y) * 256 - game->size.height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                int texY = ((d * game->box.c_sprite.frame.height) / spriteHeight) / 256;
                char *color = game->box.c_sprite.frame.addr + (4 * game->box.c_sprite.frame.width * texY) + (4 * texX);
                if((*(unsigned int *)color & 0x00FFFFFF) != 0) {
                    my_mlx_pixel_put(&game->render.frame, stripe, y, *(unsigned int *)color);
                } //paint pixel if it isn't black, black is the invisible color
            }
        }

        e++;
    }

    mlx_put_image_to_window(game->render.mlx, game->render.win, game->render.frame.img, 0, 0);

    return (1);
}
