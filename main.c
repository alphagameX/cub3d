#include "cub3d.h"

void debug_map(t_game game) {
    int i = 0;

    ft_printf("max width: %dpx\nmax height: %dpx\n", game.size.width, game.size.height);
    ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", game.texture.no.path, game.texture.so.path, game.texture.we.path, game.texture.ea.path);
    ft_printf("Sprite: %s\nFloor color: %x\nSky color: %x\n", game.box.sprite.path, game.box.floor.color, game.box.sky.color);
    ft_printf("Map width: %d\nMap height: %d\n", game.map.width, game.map.height);
    ft_printf("spawnpoint: y %d, x %d, dir: %c\n", (int)game.map.spawn.y, (int)game.map.spawn.x, game.map.spawn.dir);
    i = 0;
    while(i < game.box.sprite.nb_sprite) {
        ft_printf("s, x: %d, y: %d\n", (int)game.box.sprite.data[i].x, (int)game.box.sprite.data[i].y);
        i++;
    }
    i = 0;
    while(i < game.map.height) {
        ft_printf("%s", game.map.tmap[i]);
        ft_putchar('|');
        ft_putchar('\n');
        i++;
    }
}

void arguement_detection(int argv, char **argc, t_game *game) {
    int i;

    i = 2;
    while (i < argv)
    {
        if (ft_strnstr(argc[i], "--debug", ft_strlen(argc[i])))
            debug_map(*game);
        else if(ft_strnstr(argc[i], "--save", ft_strlen(argc[i])))
            game->settings.bmp_required = 1;
        else if(ft_strnstr(argc[i], "speed=", ft_strlen(argc[i])))
            game->settings.move_speed = get_param(game, argc[i]);
        else if(ft_strnstr(argc[i], "rot=", ft_strlen(argc[i])))
            game->settings.rot_speed = get_param(game, argc[i]);
        else if(ft_strnstr(argc[i], "hit=", ft_strlen(argc[i])))
            game->settings.hit_distance = get_param(game, argc[i]);
        else 
        {  
            ft_putstr("Error\n");
            ft_putstr("Unknow parameter found or missing or wrong\n");
            destroy_game(game);
        }
        i++;
    }
}

void register_hook(t_game *game) {
    if(game->settings.bmp_required == 0) {
        if(OS == 1)
            mlx_hook(game->render.win, 17, 1L<<5, leave_game, game);
        else if(OS == 0)
            mlx_hook(game->render.win, 33, 1L<<17, leave_game, game);
        mlx_hook(game->render.win, 02, 1L << 0, set_move, &game->render.moves);
        mlx_hook(game->render.win, 03, 1L << 1, unset_move, &game->render.moves);
    }
    mlx_loop_hook(game->render.mlx, rendering, game);
}

int main(int argv, char **argc)
{
    t_game game;
    if(argv < 2)
        return (0);
    game = parsing(is_valid_path(argc[1]));
    game.render.ray.zbuf = (double *)malloc(sizeof(double) * game.size.width);
    arguement_detection(argv, argc, &game);
    set_dir(&game);
    game.render.mlx = mlx_init();
    if(game.settings.bmp_required == 0)
        game.render.win = mlx_new_window(game.render.mlx, game.size.width, game.size.height, "cub3D");
    game.render.frame.img = mlx_new_image(game.render.mlx, game.size.width, game.size.height);
    game.render.frame.addr = mlx_get_data_addr(game.render.frame.img, &game.render.frame.bits_per_pixel, &game.render.frame.line_length, &game.render.frame.endian);
    if(game.settings.bmp_required == 0)
        mlx_put_image_to_window(game.render.mlx, game.render.win, game.render.frame.img, 0, 0);

    generate_textures(&game);
    register_hook(&game);
    mlx_loop(game.render.mlx);
    return (0);
}
