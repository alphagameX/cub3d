#include "../cub3d.h"

void debug_map(t_game game) {
    int i = 0;

    ft_printf("max width: %dpx\nmax height: %dpx\n", game.size.width, game.size.height);
    ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", game.texture.no, game.texture.so, game.texture.we, game.texture.ea);
    ft_printf("Sprite: %s\nFloor color: %s\nSky color: %s\n", game.box.c_sprite, game.box.c_floor, game.box.c_sky);
    ft_printf("Map width: %d\nMap height: %d\n", game.map.width, game.map.height);
    ft_printf("spawnpoint: y %d, x %d, dir: %c\n", (int)game.map.spawn.y, (int)game.map.spawn.x, game.map.spawn.dir);

    while(i < game.map.height) {
        ft_printf("%s", game.map.tmap[i]);
        ft_putchar('|');
        ft_putchar('\n');
        i++;
    }
}

void ft_unleak_strjoin(char **dst, char *src) {
    char *tmp = ft_strdup((const char *)*dst);
    if(**dst)
        free(*dst);
    *dst = ft_strjoin(tmp , src);
    free(tmp);
}

int map_line(char *line) {
    int i = 0;

    while(line[i]) {
        if(line[i] == '1' || line[i] == '2' || line[i] == '0')
            return (1);
        i++;
    }
    return (0);
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

void parse_smap(char *smap, t_tmap *map) {

    char **tmap = ft_split(smap, '\n');
    char *freed = NULL;

    int tmp = 0;
    int i = 0;

    int width = 0;
    int height = 0;

    // determine height and width for map
    while(tmap[height]) {
        if((tmp = ft_strlen(tmap[height])) > width)
            width = tmp;
        height++;
    }

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

    if(height < 3 || width < 3) {
        ft_putstr("Error\n");
        exit(0);
    }

    map->height = height;
    map->width = width;
    map->tmap = tmap;

    tmp = 0;
    while(tmp < height) {
        i = 0;
        while(tmap[tmp][i]) {
            if(tmap[tmp][i] == 'N' || tmap[tmp][i] == 'S' || tmap[tmp][i] == 'W' || tmap[tmp][i] == 'E') {

                map->spawn.x = tmp;
                map->spawn.y  = i;
                map->spawn.dir = tmap[tmp][i];

                if(tmap[tmp - 1][i] == ' ' || tmap[tmp + 1][i] == ' ' ||
                   tmap[tmp][i + 1] == ' ' || tmap[tmp][i - 1] == ' ') {
                    exit_failure(ft_argv_strjoin(4, "Space found at spawn -> y: ", ft_itoa(tmp), ", x: ", ft_itoa(i)));
                }

                if(tmap[tmp + 1][i] == '0')
                    tmap[tmp + 1][i] = 'X';

                if(tmap[tmp - 1][i] == '0')
                    tmap[tmp - 1][i] = 'X';

                if(tmap[tmp][i + 1] == '0')
                    tmap[tmp][i + 1] = 'X';

                if(tmap[tmp][i - 1] == '0')
                    tmap[tmp][i - 1] = 'X';
            }
            i++;
        }
        tmp++;
    }

    if(map->spawn.y == -1 || map->spawn.x == -1)
        exit_failure(ft_strdup("Not spawn found"));

    tmp = 0;
    while(tmp < height) {
        i = 0;
        while(tmap[tmp][i]) {

            if(i == 0 || tmp == 0 || tmp == height - 1) {
                if(tmap[tmp][i] == 'X' || tmap[tmp][i] == '2')
                    exit_failure(ft_argv_strjoin(4, "Space found in border -> y: ", ft_itoa(tmp), ", x: ", ft_itoa(i)));
            }

            if(tmap[tmp][i] == 'X') {

                if(tmap[tmp - 1][i] == ' ' || tmap[tmp + 1][i] == ' ' ||
                   tmap[tmp][i + 1] == ' ' || tmap[tmp][i - 1] == ' ') {
                    exit_failure(ft_argv_strjoin(4, "Space found at -> y: ", ft_itoa(tmp), ", x: ", ft_itoa(i)));
                }

                if(tmap[tmp - 1][i] == '0') {
                    tmap[tmp - 1][i] = 'X';
                    tmp = 0;
                }

                if(tmap[tmp + 1][i] == '0') {
                    tmap[tmp + 1][i] = 'X';
                    tmp = 0;
                }

                if(tmap[tmp][i + 1] == '0') {
                    tmap[tmp][i + 1] = 'X';
                    tmp = 0;
                }

                if(tmap[tmp][i - 1] == '0') {
                    tmap[tmp][i - 1] = 'X';
                    tmp = 0;
                }
            }
            i++;
        }
        tmp++;
    }
}

t_game parsing(char *file) {
    int fd = open((const char *)file, O_RDONLY);
    char *line = NULL;
    char *smap = "";

    t_game game = new_game();

    // get option
    while(get_next_line(fd, &line)) {
        if(line[0] == 'R' && game.size.width == 0 && game.size.width == 0)
            get_resolution(line, &game.size);
        else if(((line[0] == 'N' && line[1] == 'O') && !game.texture.no) ||
                ((line[0] == 'S' && line[1] == 'O') && !game.texture.so) ||
                ((line[0] == 'W' && line[1] == 'E') && !game.texture.we) ||
                ((line[0] == 'E' && line[1] == 'A') && !game.texture.ea))
            get_texture(line, &game.texture);
        else if(((line[0] == 'S' && line[1] == ' ') && !game.box.c_sprite) ||
                ((line[0] == 'F' && line[1] == ' ') && !game.box.c_floor) ||
                ((line[0] == 'C' && line[1] == ' ') && !game.box.c_sky))
            get_box(line, &game.box);
        // get map
        else {
           if(map_line(line)) {
               ft_unleak_strjoin(&smap, line);
               ft_unleak_strjoin(&smap, "\n");
           }
        }
        free(line);
    }

    if(map_line(line))
        ft_unleak_strjoin(&smap, line);
    // free last line gnl
    free(line);

    // if there is all flag before parse map
    map_valid(game);


    parse_smap(smap, &game.map);

    // free the smap because last use
    free(smap);

    return (game);
}

