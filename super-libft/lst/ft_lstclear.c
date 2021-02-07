/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:14:16 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:14:34 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*s;
	t_list	*next;

	if (!*lst)
		return ;
	s = *lst;
	while (s != NULL)
	{
		next = s->next;
		del(s->content);
		free(s);
		s = next;
	}
	*lst = NULL;
}
