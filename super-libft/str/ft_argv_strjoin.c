/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:14:46 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 17:15:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

void	ft_argv_strjoin(char **dst, int count, ...)
{
	va_list	list;
	int		i;

	i = 0;
	va_start(list, count);
	while (i < count)
	{
		ft_unleak_strjoin(dst, va_arg(list, char *));
		i++;
	}
}
