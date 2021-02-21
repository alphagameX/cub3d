/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   propagation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:40:20 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:43:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

void	reset_loop_on_zero(char **t, int *y, int x)
{
	if (t[*y - 1][x] == '0')
	{
		t[*y - 1][x] = 'X';
		*y = 0;
	}
	if (t[*y + 1][x] == '0')
	{
		t[*y + 1][x] = 'X';
		*y = 0;
	}
	if (t[*y][x + 1] == '0')
	{
		t[*y][x + 1] = 'X';
		*y = 0;
	}
	if (t[*y][x - 1] == '0')
	{
		t[*y][x - 1] = 'X';
		*y = 0;
	}
}

void	border_check(char **t, int y, int x, t_game *game)
{
	if (x == 0 || y == 0 || y == game->map.height - 1 ||
	x == game->map.width - 1)
	{
		if (t[y][x] == 'X' || t[y][x] == '2' || t[y][x] == '0' ||
		is_spawn_char(t[y][x]))
		{
			ft_putstr("Error\n");
			ft_putstr("Invalid map problem at: \n");
			ft_printf("y: %d, x: %d\n", y, x);
			destroy_game(game);
		}
	}
}

void	arround_check(char **t, int *y, int *x, t_game *game)
{
	if (t[*y][*x] == 'X')
	{
		if (t[*y - 1][*x] == ' ' || t[*y + 1][*x] == ' ' ||
				t[*y][*x + 1] == ' ' || t[*y][*x - 1] == ' ')
		{
			ft_putstr("Error\n");
			ft_putstr("Invalid map problem at: \n");
			ft_printf("y: %d, x: %d\n", *y, *x);
			destroy_game(game);
		}
		reset_loop_on_zero(t, y, *x);
	}
}

void	propagation(char **t, t_tmap map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < map.height)
	{
		x = 0;
		while (t[y][x])
		{
			border_check(t, y, x, game);
			arround_check(t, &y, &x, game);
			x++;
		}
		y++;
	}
}
