/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_osx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:59:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 18:00:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_texture(t_game *game)
{
	if (game->texture.ea.path)
		free(game->texture.ea.path);
	if (game->texture.we.path)
		free(game->texture.we.path);
	if (game->texture.so.path)
		free(game->texture.so.path);
	if (game->texture.no.path)
		free(game->texture.no.path);
	if (game->box.sprite.path)
		free(game->box.sprite.path);
}

void	free_image(t_game *game)
{
	if (game->texture.ea.tex.img != NULL)
		mlx_destroy_image(game->render.mlx, game->texture.ea.tex.img);
	if (game->texture.no.tex.img != NULL)
		mlx_destroy_image(game->render.mlx, game->texture.no.tex.img);
	if (game->texture.we.tex.img != NULL)
		mlx_destroy_image(game->render.mlx, game->texture.we.tex.img);
	if (game->texture.so.tex.img != NULL)
		mlx_destroy_image(game->render.mlx, game->texture.so.tex.img);
	if (game->box.sprite.frame.img != NULL)
		mlx_destroy_image(game->render.mlx, game->box.sprite.frame.img);
	if (game->render.frame.img != NULL)
		mlx_destroy_image(game->render.mlx, game->render.frame.img);
}

void	destroy_game(t_game *game)
{
	free_texture(game);
	if (game->map.tmap != NULL)
		free_array(game->map.tmap);
	if (game->map.gnl.all != NULL)
		free(game->map.gnl.all);
	if (game->render.ray.zbuf != NULL)
		free(game->render.ray.zbuf);
	if (game->box.sprite.nb_sprite > 0)
		free(game->box.sprite.data);
	if (game->map.smap != NULL)
		free(game->map.smap);
	free_image(game);
	if (game->render.win != NULL)
		mlx_destroy_window(game->render.mlx, game->render.win);
	if (game->render.mlx != NULL)
		free(game->render.mlx);
	exit(0);
}
