/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibady <ibady@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:11:21 by ibady             #+#    #+#             */
/*   Updated: 2025/11/29 18:33:19 by ibady            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_schmup.h"
#include <stdlib.h>

t_entitylist	*ft_lstnew(int c)
{
	t_entitylist	*new;

	new = malloc(sizeof(t_entitylist));
	if (!new)
		return (NULL);
	new->data.row = 0;
	new->data.col = 0;
	new->data.ch = c;
	return (new);
}

void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstiter_display(t_entitylist *lst)
{
	while (lst)
	{
		mvprintw(lst->data.row, lst->data.col, "%c", lst->data.ch);	
		lst = lst->next;
	}
}
