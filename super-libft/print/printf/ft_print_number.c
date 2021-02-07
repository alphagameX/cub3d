/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:59:52 by atinseau          #+#    #+#             */
/*   Updated: 2020/12/13 13:59:53 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int			ft_print_padd(int end, char c)
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

static int	ft_check_padd(t_options p, char *str, int *sign)
{
	int		temp_sign;

	(void)str;
	temp_sign = *sign;
	if (*sign == -1 && p.padd_char == '0' &&
			p.padd_size != 0 && p.reverse_padd == 0)
	{
		ft_putchar('-');
		*sign *= -1;
	}
	return (ft_print_padd(p.padd_size - p.field_size -
			((temp_sign == -1) ? 1 : 0), p.padd_char));
}

static char	*ft_check_type(char type, long long nbr)
{
	if (type == 'x' || type == 'X')
		return (ft_get_hex(type, nbr));
	return (ft_itoa_max(nbr));
}

static void	setter_minus(char **str, int *count, int *sign)
{
	*str = ft_substr(*str, 1, ft_strlen(*str));
	*count = *count + 1;
	*sign *= -1;
}

int			ft_print_number(t_options print, long long nbr)
{
	char	*nb;
	int		sign;
	int		count;

	count = 0;
	if (nbr == 0 && print.field_size == 0)
		return (ft_print_padd(print.padd_size, ' '));
	sign = 1;
	nb = ft_check_type(print.type, nbr);
	if (nb[0] == '-')
		setter_minus(&nb, &count, &sign);
	if (print.field_size < ft_strlen(nb))
		print.field_size = ft_strlen(nb);
	if (!print.reverse_padd)
		count += ft_check_padd(print, nb, &sign);
	if (sign == -1)
		ft_putchar('-');
	count += ft_print_padd(print.field_size - ft_strlen(nb), '0');
	count += ft_putstr_r(nb);
	if (print.reverse_padd)
		count += ft_check_padd(print, nb, &sign);
	free(nb);
	return (count);
}
