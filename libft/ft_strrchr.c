/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:24:28 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/01 19:45:37 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	sym;
	char	*ss;
	int		i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	ss = (char *)s + i;
	sym = c;
	if ((sym == '\0') && (*ss == sym))
		return (ss);
	while (i-- > 0)
		if (*--ss == sym)
			return (ss);
	return (0);
}
