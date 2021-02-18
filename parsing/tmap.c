#include "parsing.h"

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

void get_map_size(t_tmap *map) {
    int tmp;

    // determine height and width for map
    while(map->tmap[map->height]) {
        if((tmp = ft_strlen(map->tmap[map->height])) > map->width)
            map->width = tmp;
        map->height += 1;
    }
    if(map->height < 3 || map->width < 3)
        exit_failure("Map size is too small");
}

t_spawn get_map_spawn(char **t, t_tmap *map, t_game *game) {
    t_spawn spawn;
    int y;
    int i;
    int nb;

    nb = 0;
    y = 0;
    while(y < map->height) {
        i = 0;
        while(t[y][i]) {

            if(t[y][i] == 'N' || t[y][i] == 'S' || t[y][i] == 'W' || t[y][i] == 'E') {
                nb++;

                if(nb > 1) {
                    ft_putstr("Error\n");
                    ft_putstr("There is more than one spawn\n");
                    destroy_game(game);
                }
                spawn.x = y + 0.5;
                spawn.y  = i + 0.5;
                spawn.dir = t[y][i];

                if(t[y - 1][i] == ' ' || t[y + 1][i] == ' ' ||
                        t[y][i + 1] == ' ' || t[y][i - 1] == ' ') {
                    ft_putstr("Error\n");
                    ft_putstr("Space found arround the spawn\n");
                    ft_printf("y: %d , x: %d\n", y, i);
                    destroy_game(game);
                }

                if(t[y + 1][i] == '0')
                    t[y + 1][i] = 'X';

                if(t[y - 1][i] == '0')
                    t[y - 1][i] = 'X';

                if(t[y][i + 1] == '0')
                    t[y][i + 1] = 'X';

                if(t[y][i - 1] == '0')
                    t[y][i - 1] = 'X';
            }
            i++;
        }
        y++;
    }

    return (spawn);
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

int propagation(char **t, t_tmap map, t_game *game) {
    int y;
    int x;

    y = 0;
    x = 0;
    while(y < map.height) {
        x = 0;
        while(t[y][x]) {

            if(x == 0 || y == 0 || y == map.height - 1 || x == map.width - 1) {
                if(t[y][x] == 'X' || t[y][x] == '2' || t[y][x] == '0')
                    return (0);
            }

            if(t[y][x] == 'X') {

                if(t[y - 1][x] == ' ' || t[y + 1][x] == ' ' ||
                   t[y][x + 1] == ' ' || t[y][x - 1] == ' ') {
                    return (0);
                }

                if(t[y - 1][x] == '0') {
                    t[y - 1][x] = 'X';
                    y = 0;
                }

                if(t[y + 1][x] == '0') {
                    t[y + 1][x] = 'X';
                    y = 0;
                }

                if(t[y][x + 1] == '0') {
                    t[y][x + 1] = 'X';
                    y = 0;
                }

                if(t[y][x - 1] == '0') {
                    t[y][x - 1] = 'X';
                    y = 0;
                }
            }
            x++;
        }
        y++;
    }

    return (1);
}

int check_map_char_valid(char **map) {
    int i;
    int e;

    i = 0;
    while(map[i]) {
        e = 0;
        while(map[i][e]) {
            if(map[i][e] != '1' && map[i][e] != '2' && map[i][e] != '0' && map[i][e] != 'N' 
            &&  map[i][e] != 'S' && map[i][e] != 'W' && map[i][e] != 'E' && map[i][e] != ' ' && map[i][e] != '\n') {
                return (0);
            }
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

int parse_smap(char *smap, t_game *game) {
    int y = 0;
    int i = 0;

    game->map.tmap = ft_split(smap, '\n');
    get_map_size(&game->map);
    fix_map_whitespace(game->map.tmap, game->map.width, game->map.height);

    if(check_map_char_valid(game->map.tmap) == 0) {
        ft_putstr("Error\n");
        ft_putstr("the .cub map contain too many char type\n");
        destroy_game(game);
        return (0);
    }

    
    get_sprite(game);

    game->map.spawn = get_map_spawn(game->map.tmap, &game->map, game);

    if(propagation(game->map.tmap, game->map, game) == 0) {
        game->map.height--;
        while(game->map.height >= 0)
            free(game->map.tmap[game->map.height--]);
        return (0);
    }
    return (1);
}