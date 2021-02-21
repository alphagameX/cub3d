/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:01:24 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 18:03:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_game	new_game(void)
{
	t_game	game;

	init_all(&game);
	init_texture(&game.texture);
	init_moves(&game.render.moves);
	init_box(&game.box);
	return (game);
}

void	init_moves(t_move *moves)
{
	int	i;

	i = 0;
	moves->nb_move = 0;
	while (i < 10)
	{
		moves->wait_mode[i] = -1;
		i++;
	}
}

void	init_texture(t_texture *texture)
{
	texture->ea.path = NULL;
	texture->no.path = NULL;
	texture->so.path = NULL;
	texture->we.path = NULL;
	texture->ea.tex.img = NULL;
	texture->no.tex.img = NULL;
	texture->so.tex.img = NULL;
	texture->we.tex.img = NULL;
	texture->ea.is_see = 0;
	texture->no.is_see = 0;
	texture->so.is_see = 0;
	texture->we.is_see = 0;
}

void	init_box(t_box *box)
{
	box->sprite.path = NULL;
	box->sprite.data = NULL;
	box->sprite.frame.img = NULL;
	box->sprite.nb_sprite = 0;
	box->sprite.is_see = 0;
	box->floor.is_see = 0;
	box->sky.is_see = 0;
}

void	init_all(t_game *game)
{
	game->render.frame.img = NULL;
	game->render.win = NULL;
	game->render.mlx = NULL;
	game->size.width = 0;
	game->size.height = 0;
	game->size.is_see = 0;
	game->settings.bmp_required = 0;
	game->settings.move_speed = 0.1;
	game->settings.hit_distance = 0.3;
	game->settings.rot_speed = 0.1;
	game->map.height = 0;
	game->map.width = 0;
	game->map.spawn.y = -1;
	game->map.spawn.x = -1;
	game->map.smap = NULL;
	game->map.tmap = NULL;
	game->render.ray.zbuf = NULL;
	game->map.gnl.all = NULL;
	game->map.gnl.nb_line = 0;
}
