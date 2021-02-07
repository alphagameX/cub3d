/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <atinseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:00:03 by atinseau          #+#    #+#             */
/*   Updated: 2020/12/13 16:00:55 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft/libft.h"
# include <stdlib.h>
# define FALSE 0
# define TRUE 1

typedef struct	s_options
{
	int		reverse_padd;
	int		get_sign;
	char	padd_char;
	int		field_size;
	int		padd_size;
	char	type;
}				t_options;
int				ft_printf(const char *str, ...);
int				ft_parsing(va_list *args, char *s);
void			ft_init(t_options *print);
void			ft_get_flag(char *str, t_options *print,
							int *main_loop, va_list *args);
int				is_type(char t);
void			digit_getter(char *str, int *size,
								int *main_loop, va_list *args);
void			ft_print_flag(t_options print, va_list *args, int *count);
int				ft_print_str(t_options print, char *str);
int				ft_print_number(t_options print, long long nbr);
int				ft_print_char(t_options print, char c);
char			*ft_itoa_max(long long n);
char			*ft_get_hex(char type, unsigned long nb);
char			*ft_malloc_zero(void);
int				ft_print_addr(t_options p, unsigned long nbr);
int				ft_print_padd(int end, char c);
int				ft_putstr_r(char *str);

#endif
