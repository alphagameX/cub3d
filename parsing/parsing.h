//
// Created by Arthur Tinseau on 08/02/2021.
//

#ifndef CUB3D_PARSING_H
#define CUB3D_PARSING_H

#include "../cub3d.h"


void parse_smap(char *smap, t_game *game);
void init_moves(t_move *moves);
t_game new_game();

// map
t_spawn get_map_spawn(char **t, t_tmap *map, t_game *game);
int propagation(char **t, t_tmap map, t_game *game);
int is_spawn_char(char c);
char *fill_space(int filled);
void fix_map_whitespace(char **tmap, int width, int height);

void is_valid_texture(t_game *game);
char *check_is_valid_texture_path(char *texture_path);
int check_map_char_valid(char **map);

void get_texture(char *line, t_game *game);
void get_box(char *line, t_game *game);
void get_resolution(char *res, t_game *game);

//sprite
void push_sprite(t_game *game, int x, int y);

#endif //CUB3D_PARSING_H
