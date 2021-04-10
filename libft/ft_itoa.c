/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:35:53 by cmarsha           #+#    #+#             */
/*   Updated: 2020/11/08 16:01:40 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	n_len(int n)
{
	int	nb;

	nb = 0;
	if (n < 0)
		nb++;
	while (n)
	{
		n /= 10;
		nb++;
	}
	return (nb);
}

char		*ft_itoa(int n)
{
	char	*dest;
	int		nb;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 1;
	(nb = n_len(n)) == 0 ? nb++ : nb;
	dest = (char *)malloc(sizeof(char) * (nb + 1));
	if (!dest)
		return (0);
	dest[nb] = '\0';
	if (n < 0)
	{
		dest[0] = '-';
		sign = -1;
	}
	n *= sign;
	while (((sign == 1) && (nb > 0)) || (nb > 1))
	{
		dest[--nb] = (n % 10) + 48;
		n /= 10;
	}
	return (dest);
}
