/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibady <ibady@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:11:21 by ibady             #+#    #+#             */
/*   Updated: 2025/11/29 16:23:15 by ibady            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_schmup.h"

t_entitylist	*ft_lstnew(void *content)
{
	t_entitylist	*new;

	new = malloc(sizeof(t_entitylist));
	if (!new)
		return (NULL);
	new->next = NULL;
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

void	ft_lstiter(t_entitylist *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);	
		lst = lst->next;
	}
}
