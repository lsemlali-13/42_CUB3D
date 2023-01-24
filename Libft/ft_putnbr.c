/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 20:07:26 by rarahhal          #+#    #+#             */
/*   Updated: 2022/06/18 14:05:24 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pp(long nb1)

{
	char	c;

	if (nb1 >= 0 && nb1 <= 9)
	{
		c = nb1 + 48;
		write(1, &c, 1);
	}
	else if (nb1 > 0)
	{
		pp(nb1 / 10);
		pp(nb1 % 10);
	}
}

void	ft_putnbr(int n)
{
	long	nb2;

	write (1, "number of movements = ", 22);
	nb2 = (long)n;
	if (nb2 < 0)
	{
		write(1, "-", 1);
		nb2 = -nb2;
	}
	pp(nb2);
	write(1, "\n", 1);
}
