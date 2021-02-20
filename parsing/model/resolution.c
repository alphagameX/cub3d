#include "../parsing.h"

void free_r(char **r) {
    int i;

    i = 0;
    while(r[i])
        free(r[i++]);
    free(r);
}

void get_resolution(char *res, t_game *game) {
    int i = 0;
    char **r = ft_split(res, ' ');

    while(r[i])
        i++;
    if(i != 3) {
        ft_putstr("Error\n");
        ft_putstr("There is wrong number argument in resolution\n");
        free_r(r);
        destroy_game(game);
    } 

    if(game->size.is_see == 0)
        game->size.is_see += 1;
    else {
        ft_putstr("Error\n");
        ft_putstr("Too many R arguement\n");
        free_r(r);
        destroy_game(game);
    }

    game->size.width = ft_atoi(r[1]);
    game->size.height = ft_atoi(r[2]);
    if(game->size.height < 600) {
        ft_putstr("LOG: height is lower than min height, the height is now 600\n");
        game->size.height = 600;
    }
     if(game->size.width < 800) {
        ft_putstr("LOG: width is lower than min width, the width is now 800\n");
        game->size.width = 800;
    }
    free_r(r);
}


