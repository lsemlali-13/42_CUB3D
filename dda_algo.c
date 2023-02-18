#include "cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

double	degtorad(double ang)
{
	while (ang < 0)
		ang += 360;
	while (ang >= 360)
		ang -= 360;
	return (ang * M_PI / 180);
}

t_point	get_hsign(double ang)
{
	t_point point;

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
		// point.x = -TILE_SIZE;
		point.signx = -1;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
	{
		// point.x = -TILE_SIZE;
		point.signx = -1;
	}
	else
	{
		point.x = TILE_SIZE;
		// point.signx = -1;
	}
	return (point);
}

t_point	get_dirh(double ang)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	// if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
	// 	point.y = -1;
	if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
		point.x = -1;
	if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
		point.x = -1;
	return (point);
}

t_point	get_dirv(double ang)
{
	t_point point;

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
	t_point point;

	point.x = 0;
	point.y = 0;
	point.signx = 1;
	point.signy = 1;
	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
	{
		// point.y = -TILE_SIZE;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
	{
		// point.y = -TILE_SIZE;
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

int	is_wallh(t_player *p, int x, int y)
{
	t_point inc;

	inc = get_dirh(p->rayangle);
	x += inc.x;
	y += inc.y;
	int check = y < p->map_height / TILE_SIZE && y >= 0 && x < ft_strlen(p->map[y]) && x >= 0;
	if (!check)
		return (-1);
	if (check && p->map[y][x] == '1')
		return (1);
	return (0);
}

int	is_wallv(t_player *p, int x, int y)
{
	t_point inc;

	inc = get_dirv(p->rayangle);
	x += inc.x;
	y += inc.y;
	int check = y < p->map_height / TILE_SIZE && y >= 0 && x < ft_strlen(p->map[y]) && x >= 0;
	if (!check)
		return (-1);
	if (check && p->map[y][x] == '1')
		return (1);
	return (0);
}

void	ddah(t_player *p)
{
	// double dx = TILE_SIZE / cos(degtorad(p->rayangle));
	double hx = TILE_SIZE, hy;
	t_point inc = get_hsign(p->rayangle);
	double x = floor(p->tox / TILE_SIZE) * TILE_SIZE + inc.x, y;
	hy = fabs(fabs(x - p->x) * tan(degtorad(p->rayangle)));
	y = p->toy + (hy * inc.signy);
	hy = fabs(TILE_SIZE * tan(degtorad(p->rayangle)));
	double tx, ty;
	// int clr[2] =  {ORANGE, GREEN};
	int i = 0;
	tx = p->x;
	ty = p->y;
	int k = 0;
	while (!is_wallh(p, x / TILE_SIZE, y / TILE_SIZE))
	{
		// draw_line(tx, ty, x, y, clr[i], p);
		tx = x;
		ty = y;
		x += hx * inc.signx;
		y += hy * inc.signy;
		p->tox = x;
		p->toy = y;
		i = (i == 0 ? 1 : 0);
		k = -1;
	}
	if (is_wallh(p, x / TILE_SIZE, y / TILE_SIZE) == 1)
	{
		p->tox = x;
		p->toy = y;
		// draw_line(tx, ty, x, y, clr[i], p);
	}
	if (is_wallh(p, x / TILE_SIZE, y / TILE_SIZE) == -1)
	{
		p->tox = p->x;
		p->toy = p->y;
	}
}
void	ddav(t_player *p)
{
	// double dx = TILE_SIZE / sin(degtorad(p->rayangle));
	double hx, hy = TILE_SIZE;
	t_point inc = get_vsign(p->rayangle);
	double y = floor(p->y / TILE_SIZE) * TILE_SIZE + inc.y, x;
	hx = fabs(fabs(p->y - y) / tan(degtorad(p->rayangle)));
	x = p->x + (hx * inc.signx);
	hx = fabs(TILE_SIZE / tan(degtorad(p->rayangle)));
	double tx, ty;
	int i = 0;
	tx = p->x;
	ty = p->y;
	int k = 0;
	while (!is_wallv(p, x / TILE_SIZE, y / TILE_SIZE))
	{
		tx = x;
		ty = y;
		x += hx * inc.signx;
		y += hy * inc.signy;
		p->tox = x;
		p->toy = y;
		i = (i == 0 ? 1 : 0);
		k = -1;
	}
	if (is_wallv(p, x / TILE_SIZE, y / TILE_SIZE) == 1)
	{
		p->tox = x;
		p->toy = y;
	}
	if (is_wallv(p, x / TILE_SIZE, y / TILE_SIZE) == -1)
	{
		p->tox = p->x;
		p->toy = p->y;
	}
}

double	get_dis(double stx, double sty, double endx, double endy)
{
	return (sqrt(pow(endx - stx, 2) + pow(endy - sty, 2)));
}



void	dda(t_player *p, unsigned int *color)
{
	t_point hor;
	t_point ver;
	double dish, disv;
	ddah(p);
	hor.x = p->tox;
	hor.y = p->toy;
	ddav(p);
	ver.x = p->tox;
	ver.y = p->toy;
	dish = get_dis(p->x, p->y, hor.x, hor.y);
	disv = get_dis(p->x, p->y, ver.x, ver.y);
	p->check = 0;
	if (((dish > disv) && disv != 0) || dish == 0)
	{
		if (sin(degtorad(p->rayangle)) > 0)
		{
			p->check = -1;
		}
		else
			*color = WHITE;
		p->tox = ver.x;
		p->toy = ver.y;
	}
	else
	{
		if (cos(degtorad(p->rayangle)) > 0)
			*color = GREEN;
		else
			*color = PURPLE;
		p->tox = hor.x;
		p->toy = hor.y;
	}
}