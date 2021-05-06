/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 16:35:53 by cmarsha           #+#    #+#             */
/*   Updated: 2021/05/06 15:49:38 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_full(char *nbr, long int count, int nb, int count3)
{
	int	i;
	int	n;

	i = 0;
	n = nb;
	while ((count / 10) >= 1)
	{
		count /= 10;
		if (nb < 0)
		{
			if (nb == -2147483648)
				nb = 2147483647;
			else
				nb = -nb;
			nbr[i++] = '-';
			count /= 10;
		}
		if (n == -2147483648 && i == (count3 - 1))
			nbr[i++] = '8';
		else
			nbr[i++] = nb / count + 48;
		nb %= count;
	}
	nbr[i] = 0;
}

static int	ft_count(int nb)
{
	int	count;

	count = 1;
	if (nb < 0)
	{
		if (nb == -2147483648)
			nb = 2147483647;
		else
			nb = -nb;
		count++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*nbr;
	int			nb;
	long int	count;
	int			count2;
	int			count3;

	count = 1;
	nb = n;
	count2 = ft_count(n);
	count3 = count2;
	nbr = (char *)malloc((count2 + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	while (count2 > 0)
	{
		count *= 10;
		count2--;
	}
	ft_full(nbr, count, nb, count3);
	return (nbr);
}
