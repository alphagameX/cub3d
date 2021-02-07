/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:59:56 by atinseau          #+#    #+#             */
/*   Updated: 2020/12/13 13:59:57 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	ft_print_padd_str(int end, char c)
{
	int	i;

	i = 0;
	while (i < end)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

static int	ft_check_padd(t_options p, char *str)
{
	int	count;

	count = 0;
	if (p.reverse_padd)
		p.padd_char = ' ';
	if (p.field_size < 0 || p.field_size > ft_strlen(str))
		count += ft_print_padd_str(p.padd_size - ft_strlen(str), p.padd_char);
	else
		count += ft_print_padd_str(p.padd_size - p.field_size, p.padd_char);
	return (count);
}

static int	padd_zero(t_options p, int main, char *str)
{
	int count;

	count = 0;
	if (p.field_size < 0)
		p.field_size = ft_strlen(str);
	while (str[main] && main < p.field_size)
	{
		ft_putchar(str[main++]);
		count += 1;
	}
	return (count);
}

int			ft_print_str(t_options print, char *str)
{
	int	i;
	int	count;

	if (!str)
		str = "(null)";
	i = 0;
	count = 0;
	if (print.padd_size == 0)
		return (padd_zero(print, i, str));
	if (print.reverse_padd == 0)
		count += ft_check_padd(print, str);
	while (str[i] && (print.field_size > -1 ? i < print.field_size : 1))
	{
		ft_putchar(str[i++]);
		count += 1;
	}
	if (print.reverse_padd == 1)
		count += ft_check_padd(print, str);
	return (count);
}
