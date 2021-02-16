#include "../parsing.h"

void get_resolution(char *res, t_game *game) {
    int i = 0;
    char **r = ft_split(res, ' ');

    while(r[i])
        i++;
    if(i != 3) {
        ft_putstr("Error\n");
        ft_putstr("There is wrong number argument in resolution");
        destroy_game(game);
    } 
    game->size.width = ft_atoi(r[1]);
    game->size.height = ft_atoi(r[2]);
    i = 0;
    while(r[i])
        free(r[i++]);
    free(r);
}


