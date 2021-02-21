/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:31:16 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:35:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void is_valid_resolution(t_game *game)
{
	if ((game->size.height == 0) || (game->size.width == 0))
	{
		ft_putstr("Error\n");
		ft_putstr("Missing resolution flag\n");
		destroy_game(game);
	}
}

void	check_min_and_max_size(t_game *game, char **r)
{
	if (game->size.width < 300)
	{
		ft_putstr("Error\n");
		ft_printf("%dpx width is too low\n", game->size.width);
		free_array(r);
		destroy_game(game);
	}
	if (game->size.height < 300)
	{
		ft_putstr("Error\n");
		ft_printf("%dpx height is too low\n", game->size.height);
		free_array(r);
		destroy_game(game);
	}
}

void	fail_resolution(t_game *game, char **res, char *msg)
{
	ft_putstr("Error\n");
	ft_putstr(msg);
	free_array(res);
	destroy_game(game);
}

void	get_resolution(char *res, t_game *game)
{
	int		i;
	char	**r;

	i = 0;
	r = ft_split(res, ' ');
	while (r[i])
		i++;
	if (i != 3)
		fail_resolution(game, r, "Wrong argument number of resolution\n");
	if (game->size.is_see == 0)
		game->size.is_see += 1;
	else
		fail_resolution(game, r, "Too many R arguement\n");
	game->size.width = ft_atoi(r[1]);
	game->size.height = ft_atoi(r[2]);
	check_min_and_max_size(game, r);
	free_array(r);
}
