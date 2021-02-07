/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:23:17 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/21 19:23:20 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	b;
	size_t	l;

	i = 0;
	b = ft_strlen((char *)big);
	l = ft_strlen((char *)little);
	if (l == 0)
		return ((char *)big);
	if (len <= 0 || b < l)
		return (NULL);
	while (big[i])
	{
		j = 0;
		while (i + j < len && i + j < b && j < l && big[i + j] == little[j])
			j++;
		if (j == len || j == l)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
