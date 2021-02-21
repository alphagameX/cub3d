#include "../../cub3d.h"

void register_hook(t_game *game) {


    if(game->settings.bmp_required == 0) {
        if(OS == 1)
            mlx_hook(game->render.win, 17, 1L<<5, leave_game, game);
        else if(OS == 0)
            mlx_hook(game->render.win, 33, 1L<<17, leave_game, game);
        mlx_hook(game->render.win, 02, 1L << 0, set_move, &game->render.moves);
        mlx_hook(game->render.win, 03, 1L << 1, unset_move, &game->render.moves);
        mlx_loop_hook(game->render.mlx, rendering, game);
    } else {
        rendering(game);
    }
}