/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:38:36 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/20 12:24:19 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

double	degtorad(double ang)
{
	while (ang < 0)
		ang += 360;
	while (ang >= 360)
		ang -= 360;
	return (ang * M_PI / 180);
}

double	get_dis(double stx, double sty, double endx, double endy)
{
	return (sqrt(pow(endx - stx, 2) + pow(endy - sty, 2)));
}

void	check_wich(t_player *p, double dish, double disv, t_point hor)
{
	if (((dish > disv) && disv != 0) || dish == 0)
	{
		if (sin(degtorad(p->rayangle)) > 0)
			p->which_tex = 'N';
		else
			p->which_tex = 'S';
	}
	else
	{
		if (cos(degtorad(p->rayangle)) > 0)
			p->which_tex = 'E';
		else
			p->which_tex = 'W';
		p->tox = hor.x;
		p->toy = hor.y;
	}
}

void	dda(t_player *p)
{
	t_point	hor;
	double	dish;
	double	disv;

	ddah(p);
	hor.x = p->tox;
	hor.y = p->toy;
	ddav(p);
	dish = get_dis(p->x, p->y, hor.x, hor.y);
	disv = get_dis(p->x, p->y, p->tox, p->toy);
	check_wich(p, dish, disv, hor);
}
