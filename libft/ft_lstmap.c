/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:09:06 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/10 18:24:48 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*begin;

	if ((!lst) && ((!f) || (!del)))
		return (0);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (0);
	begin = new;
	lst = lst->next;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (new)
		{
			ft_lstadd_back(&begin, new);
			lst = lst->next;
		}
		else
			ft_lstclear(&begin, del);
	}
	return (begin);
}
