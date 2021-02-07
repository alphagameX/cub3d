/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atinseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:16:15 by atinseau          #+#    #+#             */
/*   Updated: 2020/11/20 13:16:32 by atinseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*cell;

	if (!(cell = malloc(sizeof(t_list) * 1)))
		return (NULL);
	cell->content = content;
	cell->next = NULL;
	return (cell);
}
