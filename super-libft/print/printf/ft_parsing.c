/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:59:42 by atinseau          #+#    #+#             */
/*   Updated: 2020/12/13 15:42:23 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int		ft_parsing(va_list *args, char *s)
{
	int			i;
	int			count;
	t_options	print;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			ft_init(&print);
			ft_get_flag(s + i + 1, &print, &i, args);
			ft_print_flag(print, args, &count);
		}
		else
		{
			ft_putchar(s[i]);
			count++;
		}
		i++;
	}
	return (count);
}

int		to_plus(t_options *p, int nbr)
{
	if (nbr < 0)
	{
		p->reverse_padd = 1;
		p->padd_char = ' ';
		return (nbr * -1);
	}
	else
		return (nbr);
}

void	setter_point(char *str, t_options *p, int *main, va_list *args)
{
	digit_getter(str, &p->field_size, main, args);
	if (p->field_size >= 0)
		p->padd_char = ' ';
}

void	ft_get_flag(char *str, t_options *print, int *main_loop, va_list *args)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			print->reverse_padd = 1;
		if (str[i] == '+')
			print->get_sign = 1;
		if (str[i] == '0' && print->reverse_padd == 0)
			print->padd_char = '0';
		if (ft_isdigit(str[i]) && str[i] != '0')
			digit_getter(str + i, &print->padd_size, &i, args);
		if (str[i] == '*')
			print->padd_size = to_plus(print, va_arg(*args, int));
		if (str[i] == '.')
			setter_point(str + i + 1, print, &i, args);
		if (is_type(str[i]))
		{
			print->type = str[i++];
			break ;
		}
		i++;
	}
	*main_loop += i;
}

void	digit_getter(char *str, int *size, int *main_loop, va_list *args)
{
	int		i;
	char	*temp;

	i = 0;
	if (str[i] == '*')
	{
		*size = va_arg(*args, int);
		*main_loop += 1;
		return ;
	}
	while (ft_isdigit(str[i]))
		i++;
	temp = ft_substr(str, 0, i);
	*size = ft_atoi(temp);
	free(temp);
	*main_loop += i;
}
