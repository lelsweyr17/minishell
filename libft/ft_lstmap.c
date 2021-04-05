/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:10:09 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/09 16:13:23 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *))
{
	t_list	*elem;
	t_list	*first;

	if (!lst && (!del || !f))
		return (NULL);
	if (!(elem = ft_lstnew((*f)(lst->content))))
		return (NULL);
	first = elem;
	while (lst->next)
	{
		lst = lst->next;
		elem->next = ft_lstnew((*f)(lst->content));
		if (!elem->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		else
			elem = elem->next;
	}
	return (first);
}
