/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibady <ibady@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:11:21 by ibady             #+#    #+#             */
/*   Updated: 2025/11/29 18:04:09 by ibady            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_schmup.h"

t_entitylist	*ft_lstnew(int row, int col)
{
	t_entitylist	*new;

	new = malloc(sizeof(t_entitylist));
	if (!new)
		return (NULL);
	new->data.row = row;
	new->data.col = col;
	return (new);
}

void	ft_lstadd_front(t_entitylist **lst, t_entitylist *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstdelone(t_entitylist *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstiter(t_entitylist *lst, void	(*f)())
{
	if (!f)
		return ;
	while (lst)
	{
		f(win, lst->row, lst->col, "%c", lst->ch);	
		lst = lst->next;
	}
}
