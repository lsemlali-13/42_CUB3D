/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:18:17 by lsemlali          #+#    #+#             */
/*   Updated: 2022/06/04 10:21:55 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static char	*con_cat(char *p, char *s1, char *s2)
{	
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s1[y])
	{
		p[x] = s1[y];
		x++;
		y++;
	}
	y = 0;
	while (s2[y])
	{
		p[x] = s2[y];
		x++;
		y++;
	}
	p[x] = '\0';
	return (p);
}

char	*str_join(char *s1, char *s2)
{
	char	*p;
	int		y;

	if (!s1 || !s2)
		return (0);
	y = str_len(s1, 0) + str_len(s2, 0);
	p = malloc(y + 1);
	if (p == NULL)
		return (0);
	p = con_cat(p, (char *)s1, (char *)s2);
	return (p);
}
