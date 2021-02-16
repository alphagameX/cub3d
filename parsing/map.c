#include "parsing.h"

void debug_map(t_game game) {
    int i = 0;

    ft_printf("max width: %dpx\nmax height: %dpx\n", game.size.width, game.size.height);
    ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", game.texture.no.path, game.texture.so.path, game.texture.we.path, game.texture.ea.path);
    //ft_printf("Sprite: %s\nFloor color: %s\nSky color: %s\n", game.box.c_sprite, game.box., game.box.c_sky);
    ft_printf("Map width: %d\nMap height: %d\n", game.map.width, game.map.height);
    ft_printf("spawnpoint: y %d, x %d, dir: %c\n", (int)game.map.spawn.y, (int)game.map.spawn.x, game.map.spawn.dir);

    while(i < game.map.height) {
        ft_printf("%s", game.map.tmap[i]);
        ft_putchar('|');
        ft_putchar('\n');
        i++;
    }
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

int is_texture(char *line, t_texture texture) {
    if(((line[0] == 'N' && line[1] == 'O')) ||
       ((line[0] == 'S' && line[1] == 'O')) ||
       ((line[0] == 'W' && line[1] == 'E')) ||
       ((line[0] == 'E' && line[1] == 'A')))
        return (1);
    return (0);
}

int is_box(char *line, t_box box) {
    if(((line[0] == 'S' && line[1] == ' ') ) ||
       ((line[0] == 'F' && line[1] == ' ')) ||
       ((line[0] == 'C' && line[1] == ' ') ))
        return (1);
    return (0);
}

t_game parsing(char *file) {
    int fd = open((const char *)file, O_RDONLY);
    char *line = NULL;
    char *smap = "";

    t_game game = new_game();
    // get option
    while(get_next_line(fd, &line)) {
        if(line[0] == 'R' && game.size.width == 0 && game.size.width == 0)
            get_resolution(line, &game);
        else if(is_texture(line, game.texture))
            get_texture(line, &game);
        else if(is_box(line, game.box)) {
            get_box(line, &game);
        }
        // get map
        else {
           if(map_line(line)) {
               ft_unleak_strjoin(&smap, line);
               ft_unleak_strjoin(&smap, "\n");
           }
        }

        free(line);
    }
    close(fd);
    if(map_line(line))
        ft_unleak_strjoin(&smap, line);
    free(line);

    is_valid_texture(&game);

    //map_valid(game);

    if(parse_smap(smap, &game.map) == 0)
        exit_failure("Somethings wrong with the map");
    free(smap);
    return (game);
}

