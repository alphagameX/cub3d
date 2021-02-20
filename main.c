
#include "cub3d.h"

int main(int argv, char **argc)
{

    int i;

    if(argv < 2)
        return (0);

   

    t_game game = parsing(is_valid_path(argc[1]));
    // when .cub file is parsed
    game.render.ray.zbuf = (double *)malloc(sizeof(double) * game.size.width);


   
   
    i = 2;
    while (i < argv)
    {
        if (ft_strnstr(argc[i], "--debug", ft_strlen(argc[i])))
            debug_map(game);
        else if(ft_strnstr(argc[i], "--save", ft_strlen(argc[i]))) {
            ft_putstr("save\n");
        }
        else if(ft_strnstr(argc[i], "speed=", ft_strlen(argc[i])))
            game.settings.move_speed = get_param(&game, argc[i]);
        else if(ft_strnstr(argc[i], "rot=", ft_strlen(argc[i])))
            game.settings.rot_speed = get_param(&game, argc[i]);
        else if(ft_strnstr(argc[i], "hit=", ft_strlen(argc[i])))
            game.settings.hit_distance = get_param(&game, argc[i]);
        else 
        {  
            ft_putstr("Error\n");
            ft_putstr("Unknow parameter found or missing or wrong\n");
            destroy_game(&game);
        }
        i++;
    }

     set_dir(&game);

    game.render.mlx = mlx_init();
    game.render.win = mlx_new_window(game.render.mlx, game.size.width, game.size.height, "cub3d");

    generate_textures(&game);

    game.render.frame.img = mlx_new_image(game.render.mlx, game.size.width, game.size.height);
    game.render.frame.addr = mlx_get_data_addr(game.render.frame.img, &game.render.frame.bits_per_pixel, &game.render.frame.line_length, &game.render.frame.endian);
    mlx_put_image_to_window(game.render.mlx, game.render.win, game.render.frame.img, 0, 0);

    mlx_hook(game.render.win, 17, 1L<<5, leave_game, &game);

    mlx_hook(game.render.win, 02, 1L << 0, set_move, &game.render.moves);
    mlx_hook(game.render.win, 03, 1L << 1, unset_move, &game.render.moves);
    //mlx_key_hook(game.render.win, key_hook, &game);
    mlx_loop_hook(game.render.mlx, rendering, &game);

    mlx_loop(game.render.mlx);
    // rendering endx

    //destroy_map(&game);
    return 0;
}
