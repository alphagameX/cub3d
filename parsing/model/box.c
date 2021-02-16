#include "../parsing.h"

void check_box_sprite(t_sprite *sprite, t_game *game, char *param) {
     if(sprite->is_see < 1) {
           sprite->path = check_is_valid_texture_path(param);
           sprite->is_see += 1; 
     } else {
        ft_putstr("Error\n");
        ft_putstr("More than one sprite arguments");
        free(param);
        destroy_game(game);
    }
}

void create_rgb(t_rgb *rgb, t_game *game, char *color) {
    char **str = ft_split(color, ',');
    int i = 0;
    int tmp;

    while(str[i]) {
        tmp = ft_atoi(str[i]);
        if(tmp > 255 && tmp < 0 ) {
            ft_putstr("Error\n");
            ft_putstr("One of RGB code is above 255\n");
            destroy_game(game);
        }
        i++;
    }
    if(i != 3) {
        ft_putstr("Error\n");
        ft_putstr("There is not good argument number for RGB code");
        destroy_game(game);
    }

    rgb->color = (ft_atoi(str[0]) << 16 | ft_atoi(str[1]) << 8 | ft_atoi(str[2]));
    i = 0;
    while(str[i])
        free(str[i++]);
    free(str);
}

void get_box(char *line, t_game *game) {
    char ** param = ft_split(line, ' ');
    int i = 0;

    while(param[i])
        i++;
    if(i != 2) {
        ft_putstr("Error\n");
        ft_putstr("Wrong argument number for sprite floor or sky flag\n");
        destroy_game(game);
    }

    if(**param =='S')
        check_box_sprite(&game->box.c_sprite, game, param[1]);
    if(**param == 'F') {
        create_rgb(&game->box.floor ,game , param[1]);
        free(param[1]);
    }
    if(**param == 'C') {
        create_rgb(&game->box.sky ,game , param[1]);
        free(param[1]);
    }
    free(param[0]);
    free(param);
}
