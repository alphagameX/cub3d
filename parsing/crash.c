#include "../cub3d.h"


void exit_failure(char *msg) {
    ft_putstr("Error\n");
    ft_printf("message: %s\n", msg);
    free(msg);
    exit(0);
}

void map_valid(t_game game) {
    if(game.size.width == 0 || game.size.height == 0)
    {
        ft_putstr("Error\n");
        ft_printf("Resolution is not setted or invalid...\nWIDTH: %d\nHEIGHT: %d\n", game.size.width, game.size.height);
        exit(0);
    }

    if(!game.texture.ea || !game.texture.we || !game.texture.so || !game.texture.no)
    {
        ft_putstr("Error\n");
        ft_printf("Oww some texture is missing...\nNO: %s\nSO: %s \nWE: %s\nEA: %s\n", game.texture.no, game.texture.so, game.texture.we, game.texture.ea);
        exit(0);
    }

    if(!game.box.c_sky || !game.box.c_floor || !game.box.c_sprite)
    {
        ft_putstr("Error\n");
        ft_printf("Args in box is missing...\nS: %s\nF: %s\nC: %s\n", game.box.c_sprite, game.box.c_floor, game.box.c_sky);
        exit(0);
    }
}