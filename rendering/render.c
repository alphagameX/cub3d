#include "../cub3d.h"


int move(t_game *game) {

    double rotSpeed = 0.05;
    double collions = 0.3;

    int i = 0;
    while(i < game->render.moves.nb_move && game->render.moves.wait_mode[i] != -1) {

        // UP
        if(game->render.moves.wait_mode[i] == 13) {
            if(game->map.tmap
            [(int)(game->map.spawn.x + game->render.ray.dirX * collions)]
            [(int)game->map.spawn.y] != '1')
                game->map.spawn.x += game->render.ray.dirX * 0.1;
            if(game->map.tmap
            [(int)game->map.spawn.x]
            [(int)(game->map.spawn.y + game->render.ray.dirY * collions)] != '1')
                game->map.spawn.y += game->render.ray.dirY * 0.1;
        }
        // DOWN
        if(game->render.moves.wait_mode[i] == 1) {
            if(game->map.tmap
            [(int)(game->map.spawn.x - game->render.ray.dirX * collions)]
            [(int)game->map.spawn.y] != '1')
                game->map.spawn.x -= game->render.ray.dirX * 0.1;

            if(game->map.tmap
            [(int)game->map.spawn.x]
            [(int)(game->map.spawn.y - game->render.ray.dirY * 0.1)] != '1')
                game->map.spawn.y -= game->render.ray.dirY * 0.1;
        }
        // LEFT
        if(game->render.moves.wait_mode[i] == 2) {
            if(game->map.tmap
               [(int)(game->map.spawn.x + game->render.ray.planeX * collions)]
               [(int)game->map.spawn.y] != '1')
                game->map.spawn.x += game->render.ray.planeX * 0.1;
            if(game->map.tmap
               [(int)game->map.spawn.x]
               [(int)(game->map.spawn.y + game->render.ray.planeY * collions)] != '1')
                game->map.spawn.y += game->render.ray.planeY * 0.1;
        }
        // RIGHT
        if(game->render.moves.wait_mode[i] == 0) {
            if(game->map.tmap
               [(int)(game->map.spawn.x - game->render.ray.planeX * collions)]
               [(int)game->map.spawn.y] != '1')
                game->map.spawn.x -= game->render.ray.planeX * 0.1;

            if(game->map.tmap
               [(int)game->map.spawn.x]
               [(int)(game->map.spawn.y - game->render.ray.planeY * collions)] != '1')
                game->map.spawn.y -= game->render.ray.planeY * 0.1;
        }
        // ROTATE LEFT
        if(game->render.moves.wait_mode[i] == 124) {
            double oldDirX = game->render.ray.dirX;
            game->render.ray.dirX = game->render.ray.dirX * cos(-rotSpeed) - game->render.ray.dirY * sin(-rotSpeed);
            game->render.ray.dirY = oldDirX * sin(-rotSpeed) + game->render.ray.dirY * cos(-rotSpeed);
            double oldPlaneX = game->render.ray.planeX;
            game->render.ray.planeX = game->render.ray.planeX * cos(-rotSpeed) - game->render.ray.planeY * sin(-rotSpeed);
            game->render.ray.planeY = oldPlaneX * sin(-rotSpeed) + game->render.ray.planeY * cos(-rotSpeed);
        }
        // ROTATE RIGHT
        if (game->render.moves.wait_mode[i] == 123)
        {
            double oldDirX = game->render.ray.dirX;
            game->render.ray.dirX = game->render.ray.dirX * cos(rotSpeed) - game->render.ray.dirY * sin(rotSpeed);
            game->render.ray.dirY = oldDirX * sin(rotSpeed) + game->render.ray.dirY * cos(rotSpeed);
            double oldPlaneX = game->render.ray.planeX;
            game->render.ray.planeX = game->render.ray.planeX * cos(rotSpeed) - game->render.ray.planeY * sin(rotSpeed);
            game->render.ray.planeY = oldPlaneX * sin(rotSpeed) + game->render.ray.planeY * cos(rotSpeed);
        }

        if(game->render.moves.wait_mode[i] == 53) {
            destroy_map(game);
            exit_failure(ft_argv_strjoin(1, "END"));
        }
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

int rendering(t_game *game) {
    int hit;
    int side;
    new_image(game);
    move(game);

    int x = 0;
    while(x < game->size.width)
    {
        set_start_ray(x, game);
        hit = 0; //was there a wall hit?

        rayDir(game, game->render.ray.mapX, game->render.ray.mapY);

        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if(game->render.ray.sideDistX < game->render.ray.sideDistY)
            {
                game->render.ray.sideDistX += game->render.ray.deltaDistX;
                game->render.ray.mapX += game->render.ray.stepX;
                side = 0;
            }
            else
            {
                game->render.ray.sideDistY += game->render.ray.deltaDistY;
                game->render.ray.mapY += game->render.ray.stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if(game->map.tmap[game->render.ray.mapX][game->render.ray.mapY] == '1') {
                hit = 1;
            }
        }

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
                my_mlx_pixel_put(&game->render.frame, x, y, 0x000344);
            } else if(y > game->render.ray.drawStart && y < game->render.ray.drawEnd) {
                int texY = (int)texPos & (game->texture.we.tex.width - 1);
                texPos += step;
                char *color;
                if(side == 0 && game->render.ray.rayDirX < 0)
                    color = game->texture.so.tex.addr + (4 * game->texture.we.tex.width * texY) + (4 * texX);
                else if(side == 0 && game->render.ray.rayDirX > 0)
                    color = game->texture.no.tex.addr + (4 * game->texture.we.tex.width * texY) + (4 * texX);
                else if(side == 1 && game->render.ray.rayDirY < 0)
                    color = game->texture.ea.tex.addr + (4 * game->texture.we.tex.width * texY) + (4 * texX);
                else if(side == 1 && game->render.ray.rayDirY > 0)
                    color = game->texture.we.tex.addr + (4 * game->texture.we.tex.width * texY) + (4 * texX);

                my_mlx_pixel_put(&game->render.frame, x, y, *(unsigned int *)color);
            } else if(y > game->render.ray.drawEnd) {
                my_mlx_pixel_put(&game->render.frame, x, y, 0x340434);
            }
            y++;
        }
        x++;
    }

    mlx_put_image_to_window(game->render.mlx, game->render.win, game->render.frame.img, 0, 0);

    return (1);
}