/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:59:48 by atinseau          #+#    #+#             */
/*   Updated: 2020/12/13 15:18:22 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char		*revert_hex(char *str, int len)
{
	char	*buf;
	int		i;

	if (!(buf = (char *)malloc(sizeof(char) * len + 1)))
		return (ft_malloc_zero());
	i = 0;
	while (len >= 0)
		buf[i++] = str[len--];
	buf[i] = '\0';
	return (buf);
}

char			*ft_get_hex(char type, unsigned long nb)
{
	char	*base;
	char	buf[100];
	int		pos;

	if (type == 'x' || type == 'p')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	pos = 0;
	if (nb == 0)
		return (ft_malloc_zero());
	while (nb > 0)
	{
		buf[pos] = base[nb % 16];
		pos++;
		nb /= 16;
	}
	buf[pos] = '\0';
	return (revert_hex(buf, pos - 1));
}

int				ft_addr_zero(t_options p)
{
	int	count;

	count = 0;
	if (!p.reverse_padd)
		count += ft_print_padd(p.padd_size - 2, ' ');
	ft_putstr("0x");
	if (p.reverse_padd)
		count += ft_print_padd(p.padd_size - 2, ' ');
	return (count + 2);
}

int				ft_print_padd_hex(t_options p, char *addr)
{
	int count;

	count = 0;
	ft_putstr("0x");
	count += ft_print_padd(p.field_size - ft_strlen(addr), '0');
	count += ft_putstr_r(addr);
	return (count + 2);
}

int				ft_print_addr(t_options p, unsigned long nbr)
{
	char	*addr;
	int		count;

	count = 0;
	if (nbr == 0 && p.field_size == 0)
		return (ft_addr_zero(p));
	addr = ft_get_hex(p.type, nbr);
	if (p.reverse_padd)
		count += ft_print_padd_hex(p, addr);
	count += ft_print_padd(p.padd_size - (ft_strlen(addr) + 2), ' ');
	if (!p.reverse_padd)
		count += ft_print_padd_hex(p, addr);
	free(addr);
	return (count);
}
