#include "../parsing.h"

void check_min_and_max_size(t_game *game, char **r) {
    int max_x; 
    int max_y;

    mlx_get_screen_size(game->render.mlx, &max_x, &max_y);

    if(game->size.width < 0 || game->size.width > max_x) {
        ft_putstr("Error\n");
        ft_printf("%dpx width is too low or too hight for screen resolution\n", game->size.width);
        free_array(r);
        destroy_game(game);
    }

     if(game->size.height < 0 || game->size.height > max_y) {
        ft_putstr("Error\n");
        ft_printf("%dpx height is too low or too hight for screen resolution\n", game->size.height);
        free_array(r);
        destroy_game(game);
    }
}

void get_resolution(char *res, t_game *game) {
    int i = 0;
    char **r = ft_split(res, ' ');

    while(r[i])
        i++;
    if(i != 3) {
        ft_putstr("Error\n");
        ft_putstr("There is wrong number argument in resolution\n");
        free_array(r);
        destroy_game(game);
    } 
    if(game->size.is_see == 0)
        game->size.is_see += 1;
    else {
        ft_putstr("Error\n");
        ft_putstr("Too many R arguement\n");
        free_array(r);
        destroy_game(game);
    }
    game->size.width = ft_atoi(r[1]);
    game->size.height = ft_atoi(r[2]);
    check_min_and_max_size(game, r);
    free_array(r);
}


