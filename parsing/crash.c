#include "../cub3d.h"


void exit_failure(char *msg) {
    ft_putstr("Error\n");
    ft_printf("message: %s\n", msg);
    //system("leaks cub3d");
    exit(0);
}

int check_resolution(t_size size) {
    if(size.width == 0 || size.height == 0)
        return (0);
    return (1);
}



int check_box(t_box box) {
    if(!box.c_sky || !box.c_floor || !box.c_sprite)
      return (0);
    return (1);
}

void map_valid(t_game game) {
   
}