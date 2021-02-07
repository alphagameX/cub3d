/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:13:35 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:17:21 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*s;

	s = *alst;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while (s->next != NULL)
		s = s->next;
	s->next = new;
}
