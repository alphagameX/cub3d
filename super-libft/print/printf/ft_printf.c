/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:00:01 by atinseau          #+#    #+#             */
/*   Updated: 2020/12/13 14:00:02 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int		ft_printf(const char *str, ...)
{
	va_list	list;

	va_start(list, str);
	return (ft_parsing(&list, (char *)str));
}

void	ft_init(t_options *print)
{
	print->get_sign = 0;
	print->reverse_padd = 0;
	print->padd_size = 0;
	print->field_size = -1;
	print->padd_char = ' ';
}

int		is_type(char t)
{
	if (t == 'd' ||
			t == 'p' ||
			t == 'u' ||
			t == 'x' ||
			t == '%' ||
			t == 'i' ||
			t == 's' ||
			t == 'c' ||
			t == 'X')
		return (1);
	return (0);
}
