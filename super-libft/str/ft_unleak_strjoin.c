/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unleak_strjoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:13:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:14:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_unleak_strjoin(char **dst, char *src)
{
	char *tmp;

	if (!*dst)
	{
		*dst = ft_strdup(src);
		return ;
	}
	tmp = ft_strdup(*dst);
	free(*dst);
	*dst = ft_strjoin(tmp, src);
	free(tmp);
}
