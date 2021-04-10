/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:22:28 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/21 16:32:35 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	sym;
	char	*ss;

	if (!s || !c)
		return (0);
	ss = (char *)s;
	sym = c;
	if (*ss == sym)
		return (ss);
	while (*ss)
		if (*++ss == sym)
			return (ss);
	return (0);
}
