/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:35:26 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:44:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ray_dir(t_game *game, int map_x, int map_y)
{
	if (game->render.ray.ray_dir_x < 0)
	{
		game->render.ray.step_x = -1;
		game->render.ray.side_dist_x = (double)(game->map.spawn.x - map_x) *
		game->render.ray.delta_dist_x;
	}
	else
	{
		game->render.ray.step_x = 1;
		game->render.ray.side_dist_x = (double)(map_x + 1 - game->map.spawn.x) *
		game->render.ray.delta_dist_x;
	}
	if (game->render.ray.ray_dir_y < 0)
	{
		game->render.ray.step_y = -1;
		game->render.ray.side_dist_y = (double)(game->map.spawn.y - map_y) *
		game->render.ray.delta_dist_y;
	}
	else
	{
		game->render.ray.step_y = 1;
		game->render.ray.side_dist_y = (double)(map_y + 1 - game->map.spawn.y) *
		game->render.ray.delta_dist_y;
	}
}

void	set_start_ray(int x, t_game *game)
{
	game->render.ray.angle_x = 2 * x / (double)game->size.width - 1;
	game->render.ray.ray_dir_x = game->render.ray.dir_x +
	game->render.ray.plane_x * game->render.ray.angle_x;
	game->render.ray.ray_dir_y = game->render.ray.dir_y +
	game->render.ray.plane_y * game->render.ray.angle_x;
	game->render.ray.map_x = (int)game->map.spawn.x;
	game->render.ray.map_y = (int)game->map.spawn.y;
	game->render.ray.delta_dist_x = fabs(1 / game->render.ray.ray_dir_x);
	game->render.ray.delta_dist_y = fabs(1 / game->render.ray.ray_dir_y);
}

void	dda(t_game *game, int *side)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->render.ray.side_dist_x < game->render.ray.side_dist_y)
		{
			game->render.ray.side_dist_x += game->render.ray.delta_dist_x;
			game->render.ray.map_x += game->render.ray.step_x;
			*side = 0;
		}
		else
		{
			game->render.ray.side_dist_y += game->render.ray.delta_dist_y;
			game->render.ray.map_y += game->render.ray.step_y;
			*side = 1;
		}
		if (game->map.tmap[game->render.ray.map_x][game->render.ray.map_y] ==
		'1')
			hit = 1;
	}
}

void	line_height(t_game *game)
{
	game->render.ray.line_height = (int)(game->size.height
	/ game->render.ray.perp_wall_dist);
	game->render.ray.draw_start = -game->render.ray.line_height
	/ 2 + game->size.height / 2;
	if (game->render.ray.draw_start < 0)
		game->render.ray.draw_start = 0;
	game->render.ray.draw_end = game->render.ray.line_height
	/ 2 + game->size.height / 2;
	if (game->render.ray.draw_end >= game->size.height)
		game->render.ray.draw_end = game->size.height - 1;
}
