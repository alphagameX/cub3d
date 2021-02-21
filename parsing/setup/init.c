#include "../parsing.h"


t_game new_game() {
    t_game game;
   
    init_all(&game);
    init_texture(&game.texture);
    init_moves(&game.render.moves);
    init_box(&game.box);
    return (game);
}
