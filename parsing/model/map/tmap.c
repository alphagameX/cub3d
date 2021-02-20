#include "../../parsing.h"

void get_map_size(t_game *game) {
    int tmp;

    // determine height and width for map
    while(game->map.tmap[game->map.height]) {
        ft_printf("%s\n", game->map.tmap[game->map.height]);
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

void get_sprite(t_game *game) {
    int y;
    int x;

    y = 0;
    while(game->map.tmap[y]) {
        x = 0;
        while(game->map.tmap[y][x]) {
            if(game->map.tmap[y][x] == '2')
                push_sprite(game, x, y);
            x++;
        }
        y++; 
    }
}

void parse_smap(char *smap, t_game *game) {
    game->map.tmap = ft_split(smap, '\n');
    get_map_size(game);
    //fix_map_whitespace(game->map.tmap, game->map.width, game->map.height);
    if(check_map_char_valid(game->map.tmap) == 0) {
        ft_putstr("Error\n");
        ft_putstr("the .cub map contain too many char type\n");
        destroy_game(game);
    }
    get_sprite(game);
    game->map.spawn = get_map_spawn(game->map.tmap, &game->map, game);
    if(propagation(game->map.tmap, game->map, game) == 0) {
        game->map.height--;
        while(game->map.height >= 0)
            free(game->map.tmap[game->map.height--]);
    }
}