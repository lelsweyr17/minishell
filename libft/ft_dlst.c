/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 14:59:07 by cmarsha           #+#    #+#             */
/*   Updated: 2021/04/11 14:59:39 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_dlstadd_back(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*dlist;
	t_dlist	*dprev;

	if (dlst && !*dlst)
	{
		*dlst = new;
		return ;
	}
	if (dlst && *dlst)
	{
		dlist = *dlst;
		while (dlist->next)
			dlist = dlist->next;
		dlist->next = new;
		dprev = dlist;
		dlist = dlist->next;
		dlist->prev = dprev;
	}
}

void	ft_dlstadd_front(t_dlist **dlst, t_dlist *new)
{
	if (dlst && !*dlst)
	{
		*dlst = new;
		return ;
	}
	new->next = *dlst;
	(*dlst)->prev = new;
	*dlst = new;
}

/* NEXT FUNCTIONS DOES NOT WORK PROPERLY */
int	ft_dlstsize(t_dlist *dlst)
{
	int	len;

	len = 0;
	while (dlst)
		dlst = dlst->next;
	while (dlst)
	{
		dlst = dlst->prev;
		len++;
	}
	return (len);
}

void	ft_dlstadd_next(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*dlist;
	t_dlist	*dprev;

	if (dlst && !*dlst)
	{
		*dlst = new;
		return ;
	}
	if (dlst && *dlst)
	{
		dlist = *dlst;
		dlist->next = new;
		dprev = dlist;
		dlist = dlist->next;
		dlist->prev = dprev;
	}
}
