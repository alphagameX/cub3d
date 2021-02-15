#include "../cub3d.h"


void exit_failure(char *msg) {
    ft_putstr("Error\n");
    ft_printf("message: %s\n", msg);
    system("leaks cub3d");
    exit(0);
}

int check_resolution(t_size size) {
    if(size.width == 0 || size.height == 0)
        return (0);
    return (1);
}

int check_texture(t_texture texture) {
    if(!texture.ea.path || !texture.we.path || !texture.so.path || !texture.no.path)
        return (0);
    return (1);
}

int check_box(t_box box) {
    if(!box.c_sky || !box.c_floor || !box.c_sprite)
      return (0);
    return (1);
}

void map_valid(t_game game) {
    if(check_resolution(game.size) == 0)
        exit_failure("Size screen is invalid");
    if(check_texture(game.texture) == 0)
        exit_failure("One or some textures is invalid");
    if(check_box(game.box) == 0)
        exit_failure("Sprite or hex for floor and sky is wrong");
}