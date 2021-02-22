/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 00:25:36 by atinseau          #+#    #+#             */
/*   Updated: 2021/02/22 00:25:51 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int		has_letter(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}


void has_spawn(t_game *game)
{
	if(game->map.spawn.x == -1 || game->map.spawn.y == -1)
	{
		ft_putstr("Error\n");
		ft_putstr("Has no spawn\n");
		destroy_game(game);
	}
}