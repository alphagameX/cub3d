#include "../parsing.h"

char *is_valid_path(char *path) {
    int fd;
    fd = open(path, O_RDONLY);
    char c;

    if(read(fd, &c, 0) != -1) {
        if(ft_strncmp(path + (ft_strlen(path) - 4), ".cub", 4) == 0) {
            return (path);
        }
    }

    ft_putstr("Error\n");
    ft_putstr(".cub path is invalid\n");
    exit(0);

}

double get_param(t_game *game, char *param) {
    char **r;
    int i;

    i = 0;
    r = ft_split(param, '=');
    while(r[i])
        i++;
    if(i != 2) {
        ft_putstr("Error\n");
        ft_printf("%s parameter is wrong\n", r[0]);
        destroy_game(game);
    }

    return ((double)ft_atoi(r[i - 1]) / 100);
}