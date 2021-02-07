/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:11:54 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:00:07 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	if (!dst || !src)
		return (0);
	len = ft_strlen((char *)src);
	i = 0;
	if (size == 0)
		return (len);
	while (i < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i == size)
		dst[i - 1] = '\0';
	else
		dst[i] = '\0';
	return (len);
}
