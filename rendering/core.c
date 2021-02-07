#include "../cub3d.h"

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


int key_aleady_press(int key, int *tab, int limit) {
    int i = 0;
    while(i < limit && tab[i] != -1) {
        if(tab[i] == key)
            return (1);
        i++;
    }
    return (0);
}

int set_move(int key_code, t_move *moves) {
    (void)key_code;
    (void)moves;

    if(key_aleady_press(key_code, moves->wait_mode, moves->nb_move) == 0) {
        moves->wait_mode[moves->nb_move] = key_code;
        moves->nb_move++;
    }
    return (1);
}

int unset_move(int key_code, t_move *moves) {
    (void)key_code;
    (void)moves;

    int tmp;
    int e = 0;
    int i = 0;

    while(i < moves->nb_move) {
        if(moves->wait_mode[i] == key_code) {
            fill_wait_mode(i, moves);
            moves->nb_move--;
        }
        i++;
    }
    return (1);
}