//
// Created by Arthur Tinseau on 08/02/2021.
//

#ifndef CUB3D_PARSING_H
#define CUB3D_PARSING_H

#include "../cub3d.h"

int parse_smap(char *smap, t_tmap *map);
void init_moves(t_move *moves);
t_game new_game();

void is_valid_texture(t_game *game);
char *check_is_valid_texture_path(char *texture_path);

void get_texture(char *line, t_game *game);
void get_box(char *line, t_game *game);


#endif //CUB3D_PARSING_H
