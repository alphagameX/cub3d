/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:16:41 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 20:17:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_north(t_game *game)
{
	if (game->map.spawn.dir == 'N')
	{
		game->render.ray.dir_x = -1;
		game->render.ray.dir_y = 0;
		game->render.ray.plane_x = 0;
		game->render.ray.plane_y = 0.66;
	}
}

void	set_south(t_game *game)
{
	if (game->map.spawn.dir == 'S')
	{
		game->render.ray.dir_x = 1;
		game->render.ray.dir_y = 0;
		game->render.ray.plane_x = 0;
		game->render.ray.plane_y = -0.66;
	}
}

void	set_east(t_game *game)
{
	if (game->map.spawn.dir == 'E')
	{
		game->render.ray.dir_x = 0;
		game->render.ray.dir_y = 1;
		game->render.ray.plane_x = 0.66;
		game->render.ray.plane_y = 0;
	}
}

void	set_west(t_game *game)
{
	if (game->map.spawn.dir == 'W')
	{
		game->render.ray.dir_x = 0;
		game->render.ray.dir_y = -1;
		game->render.ray.plane_x = -0.66;
		game->render.ray.plane_y = 0;
	}
}

void	set_dir(t_game *game)
{
	set_north(game);
	set_east(game);
	set_south(game);
	set_west(game);
}
