/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:16:30 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:19:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void		free_array(char **r)
{
	int i;

	i = 0;
	while (r[i])
		free(r[i++]);
	free(r);
}

char		*check_is_valid_texture_path(char *texture_path)
{
	int fd;

	if (strstr(texture_path, ".xpm") != NULL)
	{
		fd = open((const char *)texture_path, O_RDONLY);
		if (fd == -1)
		{
			return (NULL);
		}
		else
			return (texture_path);
	}
	else
	{
		return (NULL);
	}
}

int			is_texture(char *line)
{
	if (((line[0] == 'N' && line[1] == 'O')) ||
			((line[0] == 'S' && line[1] == 'O')) ||
			((line[0] == 'W' && line[1] == 'E')) ||
			((line[0] == 'E' && line[1] == 'A')))
		return (1);
	return (0);
}

int			is_box(char *line)
{
	if (((line[0] == 'S' && line[1] == ' ')) ||
			((line[0] == 'F' && line[1] == ' ')) ||
			((line[0] == 'C' && line[1] == ' ')))
		return (1);
	return (0);
}

t_game		parsing(char *file)
{
	int		i;
	t_game	game;

	game = new_game();
	complete_file(&game.map.gnl, file);
	while (i < game.map.gnl.nb_line)
	{
		if (game.map.gnl.all[i][0] == 'R')
			get_resolution(game.map.gnl.all[i], &game);
		else if (is_texture(game.map.gnl.all[i]))
			get_texture(game.map.gnl.all[i], &game);
		else if (is_box(game.map.gnl.all[i]))
			get_box(game.map.gnl.all[i], &game);
		else
			ft_argv_strjoin(&game.map.smap, 2, game.map.gnl.all[i], "\n");
		i++;
	}
	is_valid_texture(&game);
	is_valid_box(&game);
	parse_smap(&game);
	return (game);
}
