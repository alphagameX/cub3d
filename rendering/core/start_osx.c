/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_osx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:23:48 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 18:25:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	arguement_detection(int argv, char **argc, t_game *game)
{
	int i;

	i = 2;
	while (i < argv)
	{
		if (ft_strnstr(argc[i], "--debug", ft_strlen(argc[i])))
			debug_map(*game);
		else if (ft_strnstr(argc[i], "--save", ft_strlen(argc[i])))
			game->settings.bmp_required = 1;
		else if (ft_strnstr(argc[i], "speed=", ft_strlen(argc[i])))
			game->settings.move_speed = get_param(game, argc[i]);
		else if (ft_strnstr(argc[i], "rot=", ft_strlen(argc[i])))
			game->settings.rot_speed = get_param(game, argc[i]);
		else if (ft_strnstr(argc[i], "hit=", ft_strlen(argc[i])))
			game->settings.hit_distance = get_param(game, argc[i]);
		else
		{
			ft_putstr("Error\n");
			ft_putstr("Unknow parameter found or missing or wrong\n");
			destroy_game(game);
		}
		i++;
	}
}

void	start(t_game *game)
{
	set_dir(game);
	if (game->settings.bmp_required == 0)
		game->render.win = mlx_new_window(game->render.mlx,
		game->size.width, game->size.height, "cub3D");
	game->render.frame.img = mlx_new_image(game->render.mlx, game->size.width,
	game->size.height);
	game->render.frame.addr = mlx_get_data_addr(game->render.frame.img,
	&game->render.frame.bits_per_pixel, &game->render.frame.line_length,
	&game->render.frame.endian);
	if (game->settings.bmp_required == 0)
		mlx_put_image_to_window(game->render.mlx, game->render.win,
		game->render.frame.img, 0, 0);
	generate_textures(game);
	register_hook(game);
}
