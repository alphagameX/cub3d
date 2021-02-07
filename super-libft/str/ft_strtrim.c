/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:08:49 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:09:03 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen((char *)s1);
	i = 0;
	while (is_in_set(s1[i], set) && s1[i])
		i++;
	while (is_in_set(s1[len - 1], set) && len > 0)
		len--;
	if ((len - i) < 2)
		return (ft_substr(s1, i, 2));
	return (ft_substr(s1, i, len - i));
}
