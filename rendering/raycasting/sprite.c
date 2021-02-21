/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:38:33 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:12:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

double		sprite(char d, t_game *game, int e)
{
	if (d == 'X')
		return (game->box.sprite.data[e].y - game->map.spawn.x);
	if (d == 'Y')
		return (game->box.sprite.data[e].x - game->map.spawn.y);
	destroy_game(game);
	return (0);
}

double		transform(char d, t_game *game, int e)
{
	if (d == 'X')
	{
		return (game->box.sprite.inv_det * (game->render.ray.dir_y *
			sprite('X', game, e) - game->render.ray.dir_x *
			sprite('Y', game, e)));
	}
	if (d == 'Y')
	{
		return (game->box.sprite.inv_det * (-game->render.ray.plane_y *
			sprite('X', game, e) + game->render.ray.plane_x *
			sprite('Y', game, e)));
	}
	destroy_game(game);
	return (0);
}

void		set_start_sprite_ray(t_game *game, int e)
{
	game->box.sprite.inv_det = 1.0 / (game->render.ray.plane_x *
	game->render.ray.dir_y - game->render.ray.dir_x * game->render.ray.plane_y);
	game->box.sprite.sprite_screen_x = (int)((game->size.width / 2) *
	(1 + transform('X', game, e) / transform('Y', game, e)));
	game->box.sprite.sprite_height = abs((int)(game->size.height /
	(transform('Y', game, e))));
	game->box.sprite.sprite_width = abs((int)(game->size.height /
	(transform('Y', game, e))));
	game->box.sprite.draw_start_y = -game->box.sprite.sprite_height
	/ 2 + game->size.height / 2;
	game->box.sprite.draw_end_y = game->box.sprite.sprite_height
	/ 2 + game->size.height / 2;
	game->box.sprite.draw_start_x = -game->box.sprite.sprite_width
	/ 2 + game->box.sprite.sprite_screen_x;
	game->box.sprite.draw_end_x = game->box.sprite.sprite_width
	/ 2 + game->box.sprite.sprite_screen_x;
	if (game->box.sprite.draw_start_y < 0)
		game->box.sprite.draw_start_y = 0;
	if (game->box.sprite.draw_end_y >= game->size.height)
		game->box.sprite.draw_end_y = game->size.height - 1;
	if (game->box.sprite.draw_start_x < 0)
		game->box.sprite.draw_start_x = 0;
	if (game->box.sprite.draw_end_x >= game->size.width)
		game->box.sprite.draw_end_x = game->size.width - 1;
}

void		draw_sprite(t_game *game, int e)
{
	int		tex_x;
	int		tex_y;
	int		stripe;

	stripe = game->box.sprite.draw_start_x;
	while (stripe < game->box.sprite.draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-game->box.sprite.sprite_width / 2 +
		game->box.sprite.sprite_screen_x)) * game->box.sprite.frame.width /
		game->box.sprite.sprite_width) / 256;
		if (transform('Y', game, e) > 0 && stripe > 0 &&
		stripe < game->size.width && transform('Y', game, e) <
		game->render.ray.zbuf[stripe])
			draw_one_sprite(game, stripe, tex_y, tex_x);
		stripe++;
	}
}

void		sprite_casting(t_game *game)
{
	int e;

	e = 0;
	while (e < game->box.sprite.nb_sprite)
	{
		sort_sprite(&game->box.sprite, game->map.spawn);
		set_start_sprite_ray(game, e);
		draw_sprite(game, e);
		e++;
	}
}
