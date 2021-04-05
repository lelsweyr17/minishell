/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:11:52 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/06 12:05:29 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*st;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	st = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!st)
		return (NULL);
	while (s[i])
	{
		st[i] = f(i, s[i]);
		i++;
	}
	st[i] = 0;
	return (st);
}
