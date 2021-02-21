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
    int res;

    i = 0;
    r = ft_split(param, '=');
    while(r[i])
        i++;
    if(i != 2) {
        ft_putstr("Error\n");
        ft_printf("%s parameter is wrong\n", r[0]);
        i = 0;
        while(r[i])
            free(r[i++]);
        free(r);
        destroy_game(game);
    }
    res = ft_atoi(r[1]);
    i = 0;
    while(r[i])
        free(r[i++]);
    free(r);
    return ((double)res / 100);
}


void push_line(t_lines *lines, char *line) {
    t_lines new;
    int i;
    
    i = 0;
    new.nb_line = 0;
    if(!(new.all = malloc(sizeof(char *) * (lines->nb_line + 1))))
        exit(-1);
    while(i < lines->nb_line) {
        new.all[i] = ft_strdup((const char *)lines->all[i]);
        free(lines->all[i]);
        lines->all[i] = NULL;
        i++;
    }
    if(lines->nb_line > 0)
        free(lines->all); 
    new.all[i] = ft_strdup(line);
    lines->nb_line++;
    lines->all = new.all;
}

void complete_file(t_lines *gnl, char *file) {
    char *line = NULL;
    int fd;
    int ret;

    if(!file && file == NULL)
        exit(0);
    fd = open((const char *)file, O_RDONLY);
    
    ret = 1;
    while(ret != 0) {
        ret = get_next_line(fd, &line);
       
        push_line(gnl, line);
        free(line);
    }
}
