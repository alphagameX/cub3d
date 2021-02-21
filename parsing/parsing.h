/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:20:06 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:21:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H
# include "../cub3d.h"

t_game	new_game();
void	init_all(t_game *game);
void	init_texture(t_texture *texture);
void	init_moves(t_move *moves);
void	init_box(t_box *box);
void	complete_file(t_lines *gnl, char *file);
void	get_resolution(char *res, t_game *game);
int     has_letter(char *str);
char	*check_is_valid_texture_path(char *texture_path);
void	get_texture(char *line, t_game *game);
void	get_box(char *line, t_game *game);
void	parse_smap(t_game *game);
void	get_map_size(t_game *game);
t_spawn	get_map_spawn(char **t, t_tmap *map, t_game *game);
void	is_valid_coord(t_tmap map, int y, int x, t_game *game);
int		is_spawn_char(char c);
void	get_sprite(t_game *game);
void	push_sprite(t_game *game, int x, int y);
void	propagation(char **t, t_tmap map, t_game *game);
void	is_valid_texture(t_game *game);
void	is_valid_box(t_game *game);
void    is_valid_resolution(t_game *game);
void	free_array(char **r);

#endif
