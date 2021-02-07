#include "../cub3d.h"

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
            ft_putstr("Error\n");
            ft_putstr("There is extra parameter in R options\n");
            exit(0);
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
    char ** param = ft_split(line, ' ');
    int i = 0;

    while(param[i]) {
        i++;
    }
    if(i != 2) {
        ft_putstr("Error\n");
        ft_printf("Too many argument : %s", param[i - 1]);
        exit(0);
    }
    if(param[0][0] == 'N' && param[0][1] == 'O')
        texture->no = (open((const char *)param[1], O_RDONLY) == -1) ? NULL : param[1];
    if(param[0][0] == 'S' && param[0][1] == 'O')
        texture->so = (open((const char *)param[1], O_RDONLY) == -1) ? NULL : param[1];
    if(param[0][0] == 'W' && param[0][1] == 'E')
        texture->we = (open((const char *)param[1], O_RDONLY) == -1) ? NULL : param[1];
    if(param[0][0] == 'E' && param[0][1] == 'A')
        texture->ea = (open((const char *)param[1], O_RDONLY) == -1) ? NULL : param[1];
}


void get_box(char *line, t_box *box) {
    char ** param = ft_split(line, ' ');
    int i = 0;

    while(param[i])
        i++;
    if(i > 2) {
        ft_putstr("Error\n");
        ft_printf("Too many argument : %s", param[i - 1]);
        exit(0);
    }

    if(**param =='S')
        box->c_sprite = (open((const char *)param[1], O_RDONLY) == -1) ? NULL : param[1];
    if(**param == 'F')
        box->c_floor = param[1];
    if(**param == 'C')
        box->c_sky = param[1];

}
