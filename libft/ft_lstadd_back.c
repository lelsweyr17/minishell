/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:05:52 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/10 15:33:54 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *list;

	if (lst && !*lst)
	{
		*lst = new;
		return ;
	}
	if (lst && *lst)
	{
		list = *lst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
}
