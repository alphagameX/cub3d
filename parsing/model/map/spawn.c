/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:44:47 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 20:25:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

void		corner_check(t_game *game, char **t, int y, int i)
{
	if (t[y - 1][i] == ' ' || t[y + 1][i] == ' '
	|| t[y][i + 1] == ' ' || t[y][i - 1] == ' ')
	{
		ft_putstr("Error\n");
		ft_putstr("Space found arround the spawn\n");
		ft_printf("y: %d , x: %d\n", y, i);
		destroy_game(game);
	}
}

void		set_spawn(t_spawn *spawn, int y, int x, char dir)
{
	spawn->x = y + 0.5;
	spawn->y = x + 0.5;
	spawn->dir = dir;
}

void		change_char(char **t, int y, int i)
{
	if (t[y + 1][i] == '0')
		t[y + 1][i] = 'X';
	if (t[y - 1][i] == '0')
		t[y - 1][i] = 'X';
	if (t[y][i + 1] == '0')
		t[y][i + 1] = 'X';
	if (t[y][i - 1] == '0')
		t[y][i - 1] = 'X';
}

void		too_many_spawn(t_game *game, int nb)
{
	if (nb > 1)
	{
		ft_putstr("Error\n");
		ft_putstr("There is more than one spawn\n");
		destroy_game(game);
	}
}

t_spawn		get_map_spawn(char **t, t_tmap *map, t_game *game)
{
	t_spawn		spawn;
	int			y;
	int			i;
	int			nb;

	nb = 0;
	y = 0;
	spawn.x = -1;
	spawn.y = -1;
	while (y < map->height)
	{
		i = -1;
		while (t[y][++i])
		{
			if (is_spawn_char(t[y][i]))
			{
				nb++;
				is_valid_coord(*map, y, i, game);
				too_many_spawn(game, nb);
				corner_check(game, t, y, i);
				set_spawn(&spawn, y, i, t[y][i]);
				change_char(t, y, i);
			}
		}
		y++;
	}
	return (spawn);
}
