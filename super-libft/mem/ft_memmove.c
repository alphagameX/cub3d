/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:01:56 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 12:51:26 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void		fill_right(unsigned char *dest, unsigned char *src, size_t n)
{
	while (0 < n)
	{
		dest[n - 1] = src[n - 1];
		n--;
	}
}

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (d > s)
	{
		fill_right(d, s, n);
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
