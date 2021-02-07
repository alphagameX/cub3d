/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 21:34:38 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/30 18:43:48 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		has_return(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_substr(char **str, int start, int len, int is_free)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (*str == NULL)
	{
		*new = '\0';
		return (new);
	}
	while (*(*str + start) && i < len)
	{
		new[i] = *(*str + start);
		i++;
		start++;
	}
	new[i] = '\0';
	if (is_free == 1)
		free(*str);
	return (new);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	static char		*str;
	char			*temp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 ||
			!(temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (has_return(str) == 0 && (ret = read(fd, temp, BUFFER_SIZE)))
	{
		if (ret == -1)
		{
			free(temp);
			return (-1);
		}
		temp[ret] = '\0';
		str = ft_gnl_strjoin(str, temp);
	}
	free(temp);
	if (!has_return(str))
		return (last_line(line, &str));
	*line = gnl_substr(&str, 0, pos_n(str), 0);
	str = gnl_substr(&str, pos_n(str) + 1, ft_gnl_strlen(str) - pos_n(str), 1);
	return (1);
}

int		last_line(char **line, char **str)
{
	*line = gnl_substr(str, 0, ft_gnl_strlen(*str), 0);
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

int		pos_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}
