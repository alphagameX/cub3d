/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:51:34 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:53:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

void	get_sprite(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.tmap[y])
	{
		x = 0;
		while (game->map.tmap[y][x])
		{
			if (game->map.tmap[y][x] == '2')
				push_sprite(game, x, y);
			x++;
		}
		y++;
	}
}

int		is_already_add(t_sprite *sprite, int x, int y)
{
	int i;

	i = 0;
	while (i < sprite->nb_sprite)
	{
		if (sprite->data[i].y == y && sprite->data[i].x == x)
			return (1);
		i++;
	}
	return (0);
}

void	push_sprite(t_game *game, int x, int y)
{
	t_scoord	*new;
	int			i;

	i = 0;
	if (is_already_add(&game->box.sprite, x, y) == 0)
	{
		if (!(new = malloc(sizeof(t_scoord) *
		(game->box.sprite.nb_sprite + 1))))
			destroy_game(game);
		while (i < game->box.sprite.nb_sprite)
		{
			new[i].x = game->box.sprite.data[i].x;
			new[i].y = game->box.sprite.data[i].y;
			i++;
		}
		new[i].x = x + 0.5;
		new[i].y = y + 0.5;
		if (game->box.sprite.nb_sprite > 0)
			free(game->box.sprite.data);
		game->box.sprite.nb_sprite++;
		game->box.sprite.data = new;
	}
}
