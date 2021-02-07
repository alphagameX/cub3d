/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:11:33 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 00:11:49 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	i = 0;
	if (size != 0)
	{
		while (dst[i] && i < size)
			i++;
		j = 0;
		while (src[j] && j + i < size - 1)
		{
			dst[i + j] = src[j];
			j++;
		}
		if (j + i < size)
			dst[j + i] = '\0';
	}
	k = 0;
	while (src[k] != '\0')
		k++;
	return (k + i);
}
