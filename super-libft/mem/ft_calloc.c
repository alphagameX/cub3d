/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:11:29 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/19 23:14:34 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char *new;

	if (!(new = (char *)malloc(size * nmemb)))
		return (NULL);
	ft_memset((void *)new, 0, size * nmemb);
	return (void *)new;
}
