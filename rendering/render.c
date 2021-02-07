#include "../cub3d.h"

int worldMap[5][7]= {
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
};


void my_mlx_pixel_put(t_frame *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int new_image(t_game *game) {
    if(game->render.mlx)
        mlx_destroy_image(game->render.mlx, game->render.frame.img);
    game->render.frame.img = mlx_new_image(game->render.mlx, game->size.width, game->size.height);
    game->render.frame.addr = mlx_get_data_addr(game->render.frame.img, &game->render.frame.bits_per_pixel, &game->render.frame.line_length, &game->render.frame.endian);
    return (1);
}

int key_hook(int key_code,  t_game *game) {

    double rotSpeed = 0.1;

    // UP
    if (key_code == 126)
    {
        game->map.spawn.y += game->render.ray.dirY * 0.1;
        game->map.spawn.x += game->render.ray.dirX * 0.1;
    }

    // down
    if (key_code == 125)
    {
        game->map.spawn.y -= game->render.ray.dirY * 0.1;
        game->map.spawn.x -= game->render.ray.dirX * 0.1;
    }

    // right
    if (key_code == 124)
    {
        double oldDirX = game->render.ray.dirX;
        game->render.ray.dirX = game->render.ray.dirX * cos(-rotSpeed) - game->render.ray.dirY * sin(-rotSpeed);
        game->render.ray.dirY = oldDirX * sin(-rotSpeed) + game->render.ray.dirY * cos(-rotSpeed);
        double oldPlaneX = game->render.ray.planeX;
        game->render.ray.planeX = game->render.ray.planeX * cos(-rotSpeed) - game->render.ray.planeY * sin(-rotSpeed);
        game->render.ray.planeY = oldPlaneX * sin(-rotSpeed) + game->render.ray.planeY * cos(-rotSpeed);
    }

    // left
    if (key_code == 123)
    {
        double oldDirX = game->render.ray.dirX;
        game->render.ray.dirX = game->render.ray.dirX * cos(rotSpeed) - game->render.ray.dirY * sin(rotSpeed);
        game->render.ray.dirY = oldDirX * sin(rotSpeed) + game->render.ray.dirY * cos(rotSpeed);
        double oldPlaneX = game->render.ray.planeX;
        game->render.ray.planeX = game->render.ray.planeX * cos(rotSpeed) - game->render.ray.planeY * sin(rotSpeed);
        game->render.ray.planeY = oldPlaneX * sin(rotSpeed) + game->render.ray.planeY * cos(rotSpeed);
    }

    if(key_code == 53) {
        exit_failure(ft_argv_strjoin(1, "END"));
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

int rendering(t_game *game) {
    new_image(game);

    for(int x = 0; x < game->size.width; x++)
    {
        //calculate ray position and direction
        game->render.ray.angleX = 2 * x / (double)game->size.width - 1; //x-coordinate in camera space
        game->render.ray.rayDirX = game->render.ray.dirX + game->render.ray.planeX * game->render.ray.angleX;
        game->render.ray.rayDirY = game->render.ray.dirY + game->render.ray.planeY * game->render.ray.angleX;
        //which box of the map we're in
        int mapX = (int)game->map.spawn.x;
        int mapY = (int)game->map.spawn.y;

        game->render.ray.deltaDistX = fabs(1 / game->render.ray.rayDirX);
        game->render.ray.deltaDistY = fabs(1 / game->render.ray.rayDirY);

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist

        rayDir(game, mapX, mapY);

        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if(game->render.ray.sideDistX < game->render.ray.sideDistY)
            {
                game->render.ray.sideDistX += game->render.ray.deltaDistX;
                mapX += game->render.ray.stepX;
                side = 0;
            }
            else
            {
                game->render.ray.sideDistY += game->render.ray.deltaDistY;
                mapY += game->render.ray.stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if(game->map.tmap[mapX][mapY] == '1') {
                hit = 1;
            }
        }

        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if(side == 0) {
            game->render.ray.perpWallDist = (mapX - game->map.spawn.x + (1 - game->render.ray.stepX) / 2) / game->render.ray.rayDirX;
        }
        else {
            game->render.ray.perpWallDist = (mapY - game->map.spawn.y + (1 - game->render.ray.stepY) / 2) / game->render.ray.rayDirY;
        }

        //Calculate height of line to draw on screen
        int lineHeight = (int)(game->size.height / game->render.ray.perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + game->size.height / 2;

        if(drawStart < 0) {
            drawStart = 0;
        }

        int drawEnd = lineHeight / 2 + game->size.height / 2;

        if(drawEnd >= game->size.height) {
            drawEnd = game->size.height - 1;
        }

        //choose wall color
        int color;
        switch(game->map.tmap[mapX][mapY])
        {
            case '1':  color = 0xff0E8F;    break; //red
            case '2':  color = 0x12ff3D;  break; //green
            case '3':  color = 0x104Fff;   break; //blue
            case '4':  color = 0X100F7D;  break; //white
            default: color = 0x03089D; break; //yellow
        }

        //give x and y sides different brightness
        if(side == 1) {color = color / 2;}

        //draw the pixels of the stripe as a vertical line
        while(drawStart < drawEnd) {
            my_mlx_pixel_put(&game->render.frame, x, drawStart, color);
            drawStart++;
        }

    }

    mlx_put_image_to_window(game->render.mlx, game->render.win, game->render.frame.img, 0, 0);

    return (1);
}