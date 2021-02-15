#include "parsing.h"

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


