#include "../parsing.h"

void is_valid_box(t_game *game) {
    if(game->box.floor.is_see == 0 || game->box.sky.is_see == 0 || game->box.sprite.is_see == 0)
    {
        ft_putstr("Error\n");
        if(game->box.floor.is_see == 0)
            ft_putstr("Floor argument is missing\n");
        if(game->box.sky.is_see == 0)
            ft_putstr("Sky argument is missing\n");
        if(game->box.sprite.is_see == 0)
            ft_putstr("Sprite argument is missing\n");
        destroy_game(game);
    }
}

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
    char **str;
    int i = 0;
    int tmp;

    str = ft_split(color, ',');
    rgb->is_see++;
    while(str[i]) {
        tmp = ft_atoi(str[i]);
        if(tmp > 255 || tmp < 0 ) {
            ft_putstr("Error\n");
            ft_putstr("One of RGB code is above 255\n");
            free_array(str);
            destroy_game(game);
        }
        i++;
    }
    if(i != 3 || rgb->is_see > 1) {
        ft_putstr("Error\n");
        ft_putstr("RGB code have wrong arguement number or there is more than one flag\n");
        free_array(str);
        destroy_game(game);
    }
    rgb->color = (ft_atoi(str[0]) << 16 | ft_atoi(str[1]) << 8 | ft_atoi(str[2]));
    free_array(str);
}

void get_box(char *line, t_game *game) {
    char **param;
    int i;

    param = ft_split(line, ' ');
    i = 0;
    while(param[i])
        i++;
    if(i != 2) {
        ft_putstr("Error\n");
        ft_putstr("Wrong argument number for sprite floor or sky flag\n");
        free_array(param);
        destroy_game(game);
    }
    if(**param == 'S')
        check_box_sprite(&game->box.sprite, game, param[1]);
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
