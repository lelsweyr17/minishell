/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:34:55 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/03 19:10:19 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*res;
	const char	*tmp;

	tmp = s;
	tmp += start;
	res = (void *)malloc(len + 1);
	if (!res || !s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (res);
	ft_memcpy(res, tmp, len);
	res[len] = '\0';
	return (res);
}
