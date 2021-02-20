#include "../../parsing.h"


int is_spawn_char(char c) {
    if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
        return (1);
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