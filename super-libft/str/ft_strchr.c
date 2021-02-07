/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:57:08 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 12:57:21 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;
	int		i;

	if (c == '\0')
		return ((char *)s + ft_strlen((char *)s));
	i = 0;
	temp = (char *)s;
	while (temp[i] != '\0')
	{
		if (temp[i] == c)
			return (temp + i);
		i++;
		if (c == temp[i])
			return (temp + i);
	}
	return (NULL);
}
