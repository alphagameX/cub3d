#include "../../parsing.h"

void corner_check(t_game *game,char **t, int y, int i) {
    if(t[y - 1][i] == ' ' || t[y + 1][i] == ' ' || t[y][i + 1] == ' ' || t[y][i - 1] == ' ') {
        ft_putstr("Error\n");
        ft_putstr("Space found arround the spawn\n");
        ft_printf("y: %d , x: %d\n", y, i);
        destroy_game(game);
    }
}

void set_spawn(t_spawn *spawn, int y , int x, char dir) {
    spawn->x = y + 0.5;
    spawn->y  = x + 0.5;
    spawn->dir = dir;
}

void change_char(char **t, int y, int i) {
     if(t[y + 1][i] == '0')
        t[y + 1][i] = 'X';
    if(t[y - 1][i] == '0')
        t[y - 1][i] = 'X';
    if(t[y][i + 1] == '0')
        t[y][i + 1] = 'X';
    if(t[y][i - 1] == '0')
        t[y][i - 1] = 'X';
}

void is_valid_coord(t_tmap map, int y, int x, t_game *game) {
    if(y == map.height - 1 || x == map.width - 1) {
        ft_putstr("Error\n");
        ft_putstr("Spawn found on map border\n");
        destroy_game(game);
    }
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
            if(is_spawn_char(t[y][i])) {
                nb++;
                is_valid_coord(*map, y, i, game);
                if(nb > 1) {
                    ft_putstr("Error\n");
                    ft_putstr("There is more than one spawn\n");
                    destroy_game(game);
                }
                corner_check(game, t, y, i);
                set_spawn(&spawn, y, i, t[y][i]);
                change_char(t, y, i);
            }
            i++;
        }
        y++;
    }
    return (spawn);
}