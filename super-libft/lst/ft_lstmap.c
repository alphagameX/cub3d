/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:15:39 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:18:26 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	(void)del;
	new = NULL;
	while (lst != NULL)
	{
		ft_lstadd_back(&new, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (new);
}
