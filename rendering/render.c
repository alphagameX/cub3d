#include "../cub3d.h"


int move(t_game *game) {

    double rotSpeed = 0.1;

    int i = 0;
    while(i < game->render.moves.nb_move && game->render.moves.wait_mode[i] != -1) {

        if(game->render.moves.wait_mode[i] == 126) {
            if(game->map.tmap
            [(int)(game->map.spawn.x + game->render.ray.dirX * 0.1)]
            [(int)game->map.spawn.y] != '1')
                game->map.spawn.x += game->render.ray.dirX * 0.1;


            if(game->map.tmap
            [(int)game->map.spawn.x]
            [(int)(game->map.spawn.y + game->render.ray.dirY * 0.1)] != '1')
                game->map.spawn.y += game->render.ray.dirY * 0.1;
        }
        if(game->render.moves.wait_mode[i] == 125) {
            if(game->map.tmap
            [(int)(game->map.spawn.x - game->render.ray.dirX * 0.1)]
            [(int)game->map.spawn.y] != '1')
                game->map.spawn.x -= game->render.ray.dirX * 0.1;

            if(game->map.tmap
            [(int)game->map.spawn.x]
            [(int)(game->map.spawn.y - game->render.ray.dirY * 0.1)] != '1')
                game->map.spawn.y -= game->render.ray.dirY * 0.1;
        }


        if(game->render.moves.wait_mode[i] == 124) {
            double oldDirX = game->render.ray.dirX;
            game->render.ray.dirX = game->render.ray.dirX * cos(-rotSpeed) - game->render.ray.dirY * sin(-rotSpeed);
            game->render.ray.dirY = oldDirX * sin(-rotSpeed) + game->render.ray.dirY * cos(-rotSpeed);
            double oldPlaneX = game->render.ray.planeX;
            game->render.ray.planeX = game->render.ray.planeX * cos(-rotSpeed) - game->render.ray.planeY * sin(-rotSpeed);
            game->render.ray.planeY = oldPlaneX * sin(-rotSpeed) + game->render.ray.planeY * cos(-rotSpeed);
        }
        if (game->render.moves.wait_mode[i] == 123)
        {
            double oldDirX = game->render.ray.dirX;
            game->render.ray.dirX = game->render.ray.dirX * cos(rotSpeed) - game->render.ray.dirY * sin(rotSpeed);
            game->render.ray.dirY = oldDirX * sin(rotSpeed) + game->render.ray.dirY * cos(rotSpeed);
            double oldPlaneX = game->render.ray.planeX;
            game->render.ray.planeX = game->render.ray.planeX * cos(rotSpeed) - game->render.ray.planeY * sin(rotSpeed);
            game->render.ray.planeY = oldPlaneX * sin(rotSpeed) + game->render.ray.planeY * cos(rotSpeed);
        }

        if(game->render.moves.wait_mode[i] == 53)
            exit_failure(ft_argv_strjoin(1, "END"));
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

    new_image(game);
    move(game);

    int x = 0;
    while(x < game->size.width)
    {
        set_start_ray(x, game);
        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist

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
        if(side == 0) {
            game->render.ray.perpWallDist = (game->render.ray.mapX - game->map.spawn.x + (1 - game->render.ray.stepX) / 2) / game->render.ray.rayDirX;
        }
        else {
            game->render.ray.perpWallDist = (game->render.ray.mapY - game->map.spawn.y + (1 - game->render.ray.stepY) / 2) / game->render.ray.rayDirY;
        }


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

        //choose wall color
        int color;
        switch(game->map.tmap[game->render.ray.mapX][game->render.ray.mapY])
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
        while(game->render.ray.drawStart < game->render.ray.drawEnd) {
            my_mlx_pixel_put(&game->render.frame, x, game->render.ray.drawStart, color);
            game->render.ray.drawStart++;
        }
        x++;
    }

    mlx_put_image_to_window(game->render.mlx, game->render.win, game->render.frame.img, 0, 0);

    return (1);
}