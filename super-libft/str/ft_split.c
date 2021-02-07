/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:05:18 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 12:55:24 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		nb_str(char *s, char sep)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s[e] != '\0')
	{
		if (s[e] != sep && (s[e + 1] == sep || s[e + 1] == '\0'))
			i++;
		e++;
	}
	return (i);
}

static int		get_len(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
			return (i);
		i++;
	}
	return (i);
}

static char		**fill_sup_str(char **sup_str, char *str, char sep, int nb)
{
	int		e;
	int		current_len;
	int		y;

	e = -1;
	while (++e < nb)
	{
		while (*str == sep)
			str++;
		current_len = get_len(str, sep);
		if (!(sup_str[e] = (char *)malloc(sizeof(char) * (current_len + 1))))
			return (NULL);
		y = 0;
		while (y < current_len)
			sup_str[e][y++] = *str++;
		sup_str[e][y] = '\0';
	}
	sup_str[e] = NULL;
	return (sup_str);
}

char			**ft_split(char const *s, char c)
{
	char	**sup_str;
	int		nb;

	if (!s)
		return (NULL);
	nb = nb_str((char *)s, c);
	if (!(sup_str = (char **)malloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	sup_str = fill_sup_str(sup_str, (char *)s, c, nb);
	return (sup_str);
}
