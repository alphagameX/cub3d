#include "parsing.h"

void debug_map(t_game game) {
    int i = 0;

    ft_printf("max width: %dpx\nmax height: %dpx\n", game.size.width, game.size.height);
    ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", game.texture.no.path, game.texture.so.path, game.texture.we.path, game.texture.ea.path);
    ft_printf("Sprite: %s\nFloor color: %x\nSky color: %x\n", game.box.sprite.path, game.box.floor.color, game.box.sky.color);
    ft_printf("Map width: %d\nMap height: %d\n", game.map.width, game.map.height);
    ft_printf("spawnpoint: y %d, x %d, dir: %c\n", (int)game.map.spawn.y, (int)game.map.spawn.x, game.map.spawn.dir);
    i = 0;
    while(i < game.box.sprite.nb_sprite) {
        ft_printf("s, x: %d, y: %d\n", (int)game.box.sprite.data[i].x, (int)game.box.sprite.data[i].y);
        i++;
    }
    i = 0;
    while(i < game.map.height) {
        ft_printf("%s", game.map.tmap[i]);
        ft_putchar('|');
        ft_putchar('\n');
        i++;
    }
}

char *check_is_valid_texture_path(char *texture_path) {
    int fd;
    if(strstr(texture_path, ".xpm") != NULL) {
        fd = open((const char *)texture_path, O_RDONLY);
        if(fd == -1) {
            return (NULL);
        }
        else
            return (texture_path);
    } else {
        return (NULL);
    }
}


int is_texture(char *line) {
    if(((line[0] == 'N' && line[1] == 'O')) ||
       ((line[0] == 'S' && line[1] == 'O')) ||
       ((line[0] == 'W' && line[1] == 'E')) ||
       ((line[0] == 'E' && line[1] == 'A')))
        return (1);
    return (0);
}

int is_box(char *line) {
    if(((line[0] == 'S' && line[1] == ' ') ) ||
       ((line[0] == 'F' && line[1] == ' ')) ||
       ((line[0] == 'C' && line[1] == ' ') ))
        return (1);
    return (0);
}


t_game parsing(char *file) {
    int fd;
    char *line = NULL;
    char *smap = NULL;
    t_game game;

    if(!file && file == NULL)
        exit(0);
    fd = open((const char *)file, O_RDONLY);
    game = new_game();
    while(get_next_line(fd, &line)) {
        if(line[0] == 'R')
            get_resolution(line, &game);
        else if(is_texture(line))
            get_texture(line, &game);
        else if(is_box(line))
            get_box(line, &game);
        else
            ft_argv_strjoin(&smap, 2, line, "\n");
        free(line);
    }
    close(fd);
    ft_unleak_strjoin(&smap, line);
    free(line);
    is_valid_texture(&game);
    parse_smap(smap, &game);
    free(smap);
    return (game);
}

