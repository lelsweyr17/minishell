/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:40:48 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/05 16:45:34 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int len;

	len = 0;
	if (lst)
	{
		len = 1;
		while (lst->next != NULL)
		{
			len++;
			lst = lst->next;
		}
	}
	return (len);
}
