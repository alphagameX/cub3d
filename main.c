
#include "cub3d.h"

int main(int argv, char **argc) {

    int i = 0;

    t_game game = parsing(argc[1]);
    // when .cub file is parsed

    while(i < argv) {
        if(ft_strnstr(argc[i], "--debug", ft_strlen(argc[i])))
            debug_map(game);
        i++;
    }

    // rendering start

    game.render.mlx = mlx_init();
    game.render.win = mlx_new_window(game.render.mlx, game.size.width, game.size.height, "cub3d");

    generate_textures(&game);

    game.render.frame.img = mlx_new_image(game.render.mlx, game.size.width, game.size.height);
    game.render.frame.addr = mlx_get_data_addr(game.render.frame.img, &game.render.frame.bits_per_pixel, &game.render.frame.line_length, &game.render.frame.endian);
    mlx_put_image_to_window(game.render.mlx, game.render.win, game.render.frame.img, 0, 0);


    mlx_hook(game.render.win, 02, 1L<<0, set_move, &game.render.moves);
    mlx_hook(game.render.win, 03, 1L<<1, unset_move, &game.render.moves);
    //mlx_key_hook(game.render.win, key_hook, &game);
    mlx_loop_hook(game.render.mlx, rendering, &game);

    mlx_loop(game.render.mlx);
    // rendering endx

    //destroy_map(&game);
    return 0;
}
