#include "../../parsing.h"

int check_map_char_valid(char **map) {
    int i;
    int e;

    i = 0;
    while(map[i]) {
        e = 0;
        while(map[i][e]) {
            if(map[i][e] != '1' && map[i][e] != '2' && map[i][e] != '0' && map[i][e] != 'N' 
            &&  map[i][e] != 'S' && map[i][e] != 'W' && map[i][e] != 'E' && map[i][e] != ' ' && map[i][e] != '\n')
                return (0);
            e++;
        }    
        i++;
    }
    return (1);
}

char *fill_space(int filled) {
    char *str = NULL;
    int i = 0;

    if(!(str = (char *)malloc(sizeof(char) * filled + 1))) {
        ft_putstr("Error\n");
        ft_putstr("Critic memory error detected\n");
        exit(0);
    }
    while(i < filled) {
        str[i] = ' ';
        i++;
    }
    str[i] = '\0';
    return (str);
}

void fix_map_whitespace(char **tmap, int width, int height) {
    int tmp;
    int i;
    char *freed;

    tmp = 0;
    while(tmp < height) {
        i = ft_strlen(tmap[tmp]);
        if(i < width) {
            freed = fill_space(width - i);
            ft_unleak_strjoin(&tmap[tmp], freed);
            free(freed);
        }
        tmp++;
    }
}


void parse_smap(t_game *game) {
    game->map.tmap = ft_split(game->map.smap, '\n');
    free(game->map.smap);
    game->map.smap = NULL;
    get_map_size(game);
    
    fix_map_whitespace(game->map.tmap, game->map.width, game->map.height);
    if(check_map_char_valid(game->map.tmap) == 0) {
        ft_putstr("Error\n");
        ft_putstr("the .cub map contain too many char type\n");
        destroy_game(game);
    }
    get_sprite(game);
    game->map.spawn = get_map_spawn(game->map.tmap, &game->map, game);
    propagation(game->map.tmap, game->map, game);
 
}