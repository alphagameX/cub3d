/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:39:11 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 20:26:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing.h"

void	get_map_size(t_game *game)
{
	int	tmp;

	while (game->map.tmap[game->map.height])
	{
		if ((tmp = ft_strlen(game->map.tmap[game->map.height])) >
		game->map.width)
			game->map.width = tmp;
		game->map.height += 1;
	}
	if (game->map.height < 3 || game->map.width < 3)
	{
		ft_putstr("Error\n");
		ft_putstr("The map is too small\n");
		destroy_game(game);
	}
}

int		is_spawn_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	is_valid_coord(t_tmap map, int y, int x, t_game *game)
{
	if (y == map.height - 1 || x == map.width - 1)
	{
		ft_putstr("Error\n");
		ft_putstr("Spawn found on map border\n");
		destroy_game(game);
	}
}
