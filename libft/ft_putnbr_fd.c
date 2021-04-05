/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:14:26 by lelsweyr          #+#    #+#             */
/*   Updated: 2020/11/05 12:49:29 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_output(int nb, long int count, int fd)
{
	int			n;

	n = nb;
	if (nb < 0)
	{
		if (nb == -2147483648)
			nb = 2147483647;
		else
			nb = -nb;
	}
	while (count > 1)
	{
		ft_putchar_fd(nb / count + 48, fd);
		nb %= count;
		count /= 10;
	}
	if (n == -2147483648)
		ft_putchar_fd('8', fd);
	else
		ft_putchar_fd(nb + 48, fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	int			nb;
	int			nb2;
	long int	count;

	count = 1;
	nb = n;
	if (n < 0)
	{
		if (n == -2147483648)
			n = 2147483647;
		else
			n = -n;
		ft_putchar_fd('-', fd);
	}
	nb2 = n;
	while ((nb2 / count) >= 10)
	{
		n %= 10;
		count *= 10;
	}
	ft_output(nb, count, fd);
}
