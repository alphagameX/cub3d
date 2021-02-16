#include "../cub3d.h"


void exit_failure(char *msg) {
    ft_putstr("Error\n");
    ft_printf("message: %s\n", msg);
    exit(0);
}

int check_resolution(t_size size) {
    if(size.width == 0 || size.height == 0)
        return (0);
    return (1);
}


void map_valid(t_game game) {
   
}