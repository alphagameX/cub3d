/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turns.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:30:17 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:30:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	turn_left(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->render.ray.dir_x;
	old_plane_x = game->render.ray.plane_x;
	game->render.ray.dir_x = game->render.ray.dir_x * cos(-rot_speed) -
	game->render.ray.dir_y * sin(-rot_speed);
	game->render.ray.dir_y = old_dir_x * sin(-rot_speed) +
	game->render.ray.dir_y * cos(-rot_speed);
	game->render.ray.plane_x = game->render.ray.plane_x * cos(-rot_speed) -
	game->render.ray.plane_y * sin(-rot_speed);
	game->render.ray.plane_y = old_plane_x * sin(-rot_speed) +
	game->render.ray.plane_y * cos(-rot_speed);
}

void	turn_right(t_game *game, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->render.ray.dir_x;
	old_plane_x = game->render.ray.plane_x;
	game->render.ray.dir_x = game->render.ray.dir_x * cos(rot_speed) -
	game->render.ray.dir_y * sin(rot_speed);
	game->render.ray.dir_y = old_dir_x * sin(rot_speed) +
	game->render.ray.dir_y * cos(rot_speed);
	game->render.ray.plane_x = game->render.ray.plane_x * cos(rot_speed) -
	game->render.ray.plane_y * sin(rot_speed);
	game->render.ray.plane_y = old_plane_x * sin(rot_speed) +
	game->render.ray.plane_y * cos(rot_speed);
}
