/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:06:56 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:07:18 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*temp;

	temp = (char *)s;
	len = ft_strlen(temp);
	while (len >= 0)
	{
		if (temp[len] == (char)c)
			return (temp + len);
		len--;
	}
	return (NULL);
}
