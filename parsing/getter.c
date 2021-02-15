#include "../cub3d.h"

char *check_is_valid_texture_path(char *texture_path) {
    int fd;
    if(strstr(texture_path, ".xpm") != NULL) {
        fd = open((const char *)texture_path, O_RDONLY);
        close(fd);
        if(fd == -1)
            return (NULL);
        else
            return (texture_path);
    } else {
        return (NULL);
    }
}

void get_resolution(char *res, t_size *size) {
    int i = 0;
    char **r = ft_split(res + 2, ' ');

    while (r[i]) {
        if(i == 0)
            size->width = ft_atoi(r[i]);
        else if(i == 1)
            size->height = ft_atoi(r[i]);
        else {
            i = 0;
            while(r[i]) {
                free(r[i]);
                i++;
            }
            free(r);
            exit_failure("Wrong argument number in R flag");
        }
        i++;
    }
    i = 0;
    while(r[i])
        free(r[i++]);
    free(r);
    if(size->height < 480) {
        size->height = 480;
        ft_putstr("log: height min 480px !");
    }
    if(size ->width < 480) {
        size->width = 480;
        ft_putstr("log: width min 480px !\n");
    }
}

void get_texture(char *line, t_texture *texture) {
    char **param = ft_split(line, ' ');
    int i = 0;


    while(param[i]) {
        i++;
    }
    if(i != 2)
        exit_failure("One texture flags as wrong argument number");
    if(param[0][0] == 'N' && param[0][1] == 'O')
        texture->no.path = check_is_valid_texture_path(param[1]);
    if(param[0][0] == 'S' && param[0][1] == 'O')
        texture->so.path = check_is_valid_texture_path(param[1]);
    if(param[0][0] == 'W' && param[0][1] == 'E')
        texture->we.path = check_is_valid_texture_path(param[1]);
    if(param[0][0] == 'E' && param[0][1] == 'A')
        texture->ea.path = check_is_valid_texture_path(param[1]);
    free(param[0]);

    i = 0;
}

int get_box(char *line, t_box *box) {
    char ** param = ft_split(line, ' ');
    int i = 0;

    while(param[i])
        i++;
    if(i != 2)
        return (0);

    if(**param =='S')
        box->c_sprite = (open((const char *)param[1], O_RDONLY) == -1) ? NULL : param[1];
    if(**param == 'F')
        box->c_floor = param[1];
    if(**param == 'C')
        box->c_sky = param[1];

    free(param[0]);

    return (1);
}
