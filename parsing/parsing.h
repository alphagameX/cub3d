//
// Created by Arthur Tinseau on 08/02/2021.
//

#ifndef CUB3D_PARSING_H
#define CUB3D_PARSING_H

#include "../cub3d.h"

/*INIT*/
void init_all(t_game *game);
void init_texture(t_texture *texture);
void init_moves(t_move *moves);
void init_box(t_box *box);
void get_resolution(char *res, t_game *game);
char *check_is_valid_texture_path(char *texture_path);
void get_texture(char *line, t_game *game);
void get_box(char *line, t_game *game);
void parse_smap(char *smap, t_game *game);
void get_map_size(t_game *game);
t_spawn get_map_spawn(char **t, t_tmap *map, t_game *game);
int is_spawn_char(char c);
void get_sprite(t_game *game);
void push_sprite(t_game *game, int x, int y);
int propagation(char **t, t_tmap map, t_game *game);
void is_valid_texture(t_game *game);

void free_array(char **r);

#endif //CUB3D_PARSING_H
