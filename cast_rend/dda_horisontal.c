/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_horisontal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:14:51 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/21 12:44:09 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

t_point	get_hsign(double ang)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	point.signx = 1;
	point.signy = 1;
	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
	{
		point.x = TILE_SIZE;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
	{
		point.signx = -1;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
		point.signx = -1;
	else
		point.x = TILE_SIZE;
	return (point);
}

t_point	get_dirh(double ang)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
		point.x = -1;
	if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
		point.x = -1;
	return (point);
}

int	is_wallh(t_player *p, int x, int y)
{
	t_point	inc;

	inc = get_dirh(p->rayangle);
	x += inc.x;
	y += inc.y;
	if (!(y < p->map_height / TILE_SIZE && y >= 0 \
		&& x < ft_strlen(p->map->map[y]) && x >= 0))
		return (-1);
	else if (p->map->map[y][x] == '1')
		return (1);
	return (0);
}

void	ddah_code(t_player *p, t_point inc, t_point grid, t_point d)
{
	while (!is_wallh(p, grid.x / TILE_SIZE, grid.y / TILE_SIZE))
	{
		grid.x += d.x * inc.signx;
		grid.y += d.y * inc.signy;
		p->tox = grid.x;
		p->toy = grid.y;
	}
	if (is_wallh(p, grid.x / TILE_SIZE, grid.y / TILE_SIZE) == 1)
	{
		p->tox = grid.x;
		p->toy = grid.y;
	}
	if (is_wallh(p, grid.x / TILE_SIZE, grid.y / TILE_SIZE) == -1)
	{
		p->tox = p->x;
		p->toy = p->y;
	}
}

void	ddah(t_player *p)
{
	t_point	d;
	t_point	inc;
	t_point	grid;

	inc = get_hsign(p->rayangle);
	d.x = TILE_SIZE;
	grid.x = floor(p->tox / TILE_SIZE) * TILE_SIZE + inc.x;
	d.y = fabs(fabs(grid.x - p->x) * tan(degtorad(p->rayangle)));
	grid.y = p->toy + (d.y * inc.signy);
	d.y = fabs(TILE_SIZE * tan(degtorad(p->rayangle)));
	ddah_code(p, inc, grid, d);
}
