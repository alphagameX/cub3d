/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:10:42 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 12:59:04 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		e;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) *
			(ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1)))
		return (NULL);
	e = 0;
	while (*s1 != '\0')
		new[e++] = *s1++;
	while (*s2 != '\0')
		new[e++] = *s2++;
	new[e] = '\0';
	return (new);
}
