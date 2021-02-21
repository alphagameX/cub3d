/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:38:36 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:39:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_one_sprite(t_game *game, int stripe, int tex_y, int tex_x)
{
	int		y;
	char	*color;
	int		d;

	y = game->box.sprite.draw_start_y;
	while (y < game->box.sprite.draw_end_y)
	{
		d = (y) * 256 - game->size.height * 128 +
			game->box.sprite.sprite_height * 128;
		tex_y = ((d * game->box.sprite.frame.height) /
				game->box.sprite.sprite_height) / 256;
		color = get_color(&game->box.sprite.frame.addr,
				game->box.sprite.frame.width, tex_y, tex_x);
		if ((*(unsigned int *)color & 0x00FFFFFF) != 0)
		{
			my_mlx_pixel_put(&game->render.frame, stripe,
					y, *(unsigned int *)color);
		}
		y++;
	}
}
