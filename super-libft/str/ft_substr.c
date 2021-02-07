/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:09:26 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:10:30 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	if (!(new = (char *)malloc(sizeof(char) * len + 1)))
	{
		return (NULL);
	}
	if (start >= (unsigned)ft_strlen((char *)s))
	{
		*new = '\0';
		return (new);
	}
	while (s[start] != '\0' && i < len)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}
