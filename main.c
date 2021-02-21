/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:28:17 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 20:31:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_game game)
{
	int i;

	i = 0;
	while (i < game.box.sprite.nb_sprite)
	{
		ft_printf("s, x: %d, y: %d\n", (int)game.box.sprite.data[i].x,
		(int)game.box.sprite.data[i].y);
		i++;
	}
	i = 0;
	while (i < game.map.height)
	{
		ft_printf("%s", game.map.tmap[i]);
		ft_putchar('|');
		ft_putchar('\n');
		i++;
	}
}

void	debug_map(t_game game)
{
	ft_printf("max width: %dpx\nmax height: %dpx\n", game.size.width,
	game.size.height);
	ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", game.texture.no.path,
	game.texture.so.path, game.texture.we.path, game.texture.ea.path);
	ft_printf("Sprite: %s\nFloor color: %x\nSky color: %x\n",
	game.box.sprite.path, game.box.floor.color, game.box.sky.color);
	ft_printf("Map width: %d\nMap height: %d\n", game.map.width,
	game.map.height);
	ft_printf("spawnpoint: y %d, x %d, dir: %c\n", (int)game.map.spawn.y,
	(int)game.map.spawn.x, game.map.spawn.dir);
	print_map(game);
}

int		main(int argv, char **argc)
{
	t_game game;

	if (argv < 2)
		return (0);
	game = parsing(is_valid_path(argc[1]));
	game.render.ray.zbuf = (double *)malloc(sizeof(double) * game.size.width);
	arguement_detection(argv, argc, &game);
	game.render.mlx = mlx_init();
	start(&game);
	mlx_loop(game.render.mlx);
	return (0);
}
