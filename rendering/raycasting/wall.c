/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:13:02 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 20:01:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

double		width_wall(t_game *game, int side)
{
	double	wall_x;

	if (side == 0)
		wall_x = game->map.spawn.y + game->render.ray.perp_wall_dist *
			game->render.ray.ray_dir_y;
	else
		wall_x = game->map.spawn.x + game->render.ray.perp_wall_dist *
			game->render.ray.ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

int			width_tex(t_game *game, double wall_x, int side)
{
	int tex_x;

	tex_x = (int)(wall_x * (double)game->texture.we.tex.width);
	if (side == 0 && game->render.ray.ray_dir_x > 0)
		tex_x = game->texture.we.tex.width - tex_x - 1;
	if (side == 1 && game->render.ray.ray_dir_y < 0)
		tex_x = game->texture.we.tex.width - tex_x - 1;
	return (tex_x);
}

char		*select_texture(t_game *game, int side, int tex_y, int tex_x)
{
	if (side == 0 && game->render.ray.ray_dir_x < 0)
	{
		return (get_color(&game->texture.no.tex.addr,
					game->texture.no.tex.width, tex_y, tex_x));
	}
	else if (side == 0 && game->render.ray.ray_dir_x > 0)
	{
		return (get_color(&game->texture.so.tex.addr,
					game->texture.so.tex.width, tex_y, tex_x));
	}
	else if (side == 1 && game->render.ray.ray_dir_y < 0)
	{
		return (get_color(&game->texture.we.tex.addr,
					game->texture.we.tex.width, tex_y, tex_x));
	}
	else if (side == 1 && game->render.ray.ray_dir_y > 0)
	{
		return (get_color(&game->texture.ea.tex.addr,
					game->texture.ea.tex.width, tex_y, tex_x));
	}
	return (NULL);
}

void		draw_all_wall(t_game *game, t_wall *wall, int side, int x)
{
	wall->tex_y = (int)wall->tex_pos & (game->texture.we.tex.width - 1);
	wall->tex_pos += 1.0 * game->texture.we.tex.height /
		game->render.ray.line_height;
	my_mlx_pixel_put(&game->render.frame, x, wall->y,
	*(unsigned int*)select_texture(game, side, wall->tex_y, wall->tex_x));
}

void		wall_casting(t_game *game, int side, int x)
{
	t_wall wall;

	wall.wall_x = width_wall(game, side);
	wall.tex_x = width_tex(game, wall.wall_x, side);
	wall.tex_pos = (game->render.ray.draw_start - game->size.height / 2 +
			game->render.ray.line_height / 2) * (1.0 *
			game->texture.we.tex.height / game->render.ray.line_height);
	wall.y = 0;
	while (wall.y < game->size.height)
	{
		if (wall.y < game->render.ray.draw_start)
			my_mlx_pixel_put(&game->render.frame, x, wall.y,
			game->box.floor.color);
		else if (wall.y >= game->render.ray.draw_start && wall.y <=
				game->render.ray.draw_end)
			draw_all_wall(game, &wall, side, x);
		else if (wall.y > game->render.ray.draw_end)
			my_mlx_pixel_put(&game->render.frame, x, wall.y,
			game->box.sky.color);
		wall.y++;
	}
}
