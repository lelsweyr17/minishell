/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:26:04 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/04 20:47:48 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_findset(char *c, char *set)
{
	while (*set)
		if (*set++ == *c)
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*tmp;
	size_t	len;
	int		i;

	i = 0;
	tmp = (char *)s1;
	if (!s1 || !set)
		return (0);
	while (ft_findset(tmp, (char *)set) == 1)
		tmp++;
	(len = ft_strlen(tmp)) == 0 ? 1 : (len -= 1);
	tmp += len;
	while (ft_findset(tmp, (char *)set) == 1)
	{
		tmp--;
		i++;
	}
	tmp -= (len - i);
	res = malloc((len - i + 2) * sizeof(char));
	if (!res)
		return (0);
	ft_memcpy(res, tmp, len - i + 1);
	res[len - i + 1] = '\0';
	return ((char *)res);
}
