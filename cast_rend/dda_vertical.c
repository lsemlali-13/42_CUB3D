/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_vertical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:16:19 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/22 12:44:30 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

t_point	get_dirv(double ang)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
		point.y = -1;
	if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
		point.y = -1;
	return (point);
}

t_point	get_vsign(double ang)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	point.signx = 1;
	point.signy = 1;
	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
		point.signy = -1;
	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
	{
		point.signx = -1;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
	{
		point.signx = -1;
		point.y = TILE_SIZE;
	}
	else
	{
		point.y = TILE_SIZE;
	}
	return (point);
}

int	is_wallv(t_player *p, int x, int y)
{
	t_point	inc;

	inc = get_dirv(p->rayangle);
	x += inc.x;
	y += inc.y;
	if (!(y < p->map_height / TILE_SIZE && y >= 0 \
		&& x < ft_strlen(p->map->map[y]) && x >= 0))
		return (-1);
	else if (p->map->map[y][x] == '1')
		return (1);
	return (0);
}

void	ddav_code(t_player *p, t_point inc, t_point grid, t_point d)
{
	while (!is_wallv(p, grid.x / TILE_SIZE, grid.y / TILE_SIZE))
	{
		grid.x += d.x * inc.signx;
		grid.y += d.y * inc.signy;
		p->tox = grid.x;
		p->toy = grid.y;
	}
	if (is_wallv(p, grid.x / TILE_SIZE, grid.y / TILE_SIZE) == 1)
	{
		p->tox = grid.x;
		p->toy = grid.y;
	}
	if (is_wallv(p, grid.x / TILE_SIZE, grid.y / TILE_SIZE) == -1)
	{
		p->tox = p->x;
		p->toy = p->y;
	}
}

void	ddav(t_player *p)
{
	t_point	d;
	t_point	grid;
	t_point	inc;

	inc = get_vsign(p->rayangle);
	d.y = TILE_SIZE;
	grid.y = floor(p->y / TILE_SIZE) * TILE_SIZE + inc.y;
	d.x = fabs(fabs(p->y - grid.y) / tan(degtorad(p->rayangle)));
	grid.x = p->x + (d.x * inc.signx);
	d.x = fabs(TILE_SIZE / tan(degtorad(p->rayangle)));
	ddav_code(p, inc, grid, d);
}
