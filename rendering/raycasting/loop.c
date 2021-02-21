/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:32:48 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:43:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_perp_wall_dist(t_game *game, int side)
{
	if (side == 0)
		game->render.ray.perp_wall_dist = (game->render.ray.map_x -
				game->map.spawn.x + (1 - game->render.ray.step_x) / 2) /
			game->render.ray.ray_dir_x;
	else
		game->render.ray.perp_wall_dist = (game->render.ray.map_y -
				game->map.spawn.y + (1 - game->render.ray.step_y) / 2) /
			game->render.ray.ray_dir_y;
}

int		rendering(t_game *game)
{
	int	side;
	int	x;

	if (game->settings.bmp_required == 0)
		move(game);
	x = 0;
	while (x < game->size.width)
	{
		set_start_ray(x, game);
		ray_dir(game, game->render.ray.map_x, game->render.ray.map_y);
		dda(game, &side);
		set_perp_wall_dist(game, side);
		line_height(game);
		wall_casting(game, side, x);
		game->render.ray.zbuf[x] = game->render.ray.perp_wall_dist;
		x++;
	}
	sprite_casting(game);
	if (game->settings.bmp_required == 1)
		file_bmp(game);
	mlx_put_image_to_window(game->render.mlx, game->render.win,
			game->render.frame.img, 0, 0);
	return (1);
}
