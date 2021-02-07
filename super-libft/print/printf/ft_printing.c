/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:00:07 by atinseau          #+#    #+#             */
/*   Updated: 2020/12/13 14:00:08 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_print_padd_char(char type, int padd_size, int field_size, char c)
{
	int	count;

	(void)type;
	count = 0;
	while (padd_size - field_size > 0)
	{
		ft_putchar(c);
		padd_size--;
		count++;
	}
	return (count);
}

void		ft_print_flag(t_options print, va_list *args, int *count)
{
	if (print.type == 'd' || print.type == 'i')
		*count += ft_print_number(print, va_arg(*args, int));
	else if (print.type == 'u' || print.type == 'x' || print.type == 'X')
		*count += ft_print_number(print, va_arg(*args, unsigned int));
	else if (print.type == 's')
		*count += ft_print_str(print, va_arg(*args, char *));
	else if (print.type == 'c')
		*count += ft_print_char(print, va_arg(*args, int));
	else if (print.type == '%')
		*count += ft_print_char(print, '%');
	else if (print.type == 'p')
		*count += ft_print_addr(print, va_arg(*args, unsigned long));
}

int			ft_print_char(t_options print, char c)
{
	int count;

	count = 0;
	if (!print.reverse_padd)
		count += ft_print_padd_char(print.type,
				print.padd_size, 1, print.padd_char);
	ft_putchar(c);
	count++;
	if (print.reverse_padd)
		count += ft_print_padd_char(print.type, print.padd_size, 1, ' ');
	return (count);
}
