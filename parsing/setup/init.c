#include "../parsing.h"



void set_one_dir(t_ray *ray, int dirX, int dirY, double planeX, double planeY) {
    ray->dirX = dirX;
    ray->dirY = dirY;
    ray->planeX = planeX;
    ray->planeY = planeY;
}

void set_dir(t_game *game) {
    if(game->map.spawn.dir == 'N')
        set_one_dir(&game->render.ray, -1, 0, 0, 0.66);
     if(game->map.spawn.dir == 'W') 
         set_one_dir(&game->render.ray, 0, -1, -0.66, 0);
     if(game->map.spawn.dir == 'S') 
          set_one_dir(&game->render.ray, 1, 0, 0, -0.66);
     if(game->map.spawn.dir == 'E')
          set_one_dir(&game->render.ray, 0, 1, 0.66, 0);
}


t_game new_game() {
    t_game game;
   
    init_all(&game);
    init_texture(&game.texture);
    init_moves(&game.render.moves);
    init_box(&game.box);
    return (game);
}
