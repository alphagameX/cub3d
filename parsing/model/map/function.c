#include "../../parsing.h"

void get_map_size(t_game *game) {
    int tmp;

    while(game->map.tmap[game->map.height]) {
        if((tmp = ft_strlen(game->map.tmap[game->map.height])) > game->map.width)
            game->map.width = tmp;
        game->map.height += 1;
    }
    if(game->map.height < 3 || game->map.width < 3) {
        ft_putstr("Error\n");
        ft_putstr("The map is too small\n");
        destroy_game(game);
    }
        
}

int is_spawn_char(char c) {
    if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
        return (1);
    return (0);
}
