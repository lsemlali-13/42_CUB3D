#include "cub3d.h"

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
		point.x = 50;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
	{
		// point.x = -50;
		point.signx = -1;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
	{
		// point.x = -50;
		point.signx = -1;
	}
	else
	{
		point.x = 50;
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
		// point.y = -50;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
	{
		// point.y = -50;
		point.signx = -1;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
	{
		point.signx = -1;
		point.y = 50;
	}
	else
	{
		point.y = 50;
	}
	return (point);
}

int	is_wallh(t_player *p, int x, int y)
{
	t_point inc;

	inc = get_dirh(p->rayangle);
	x += inc.x;
	y += inc.y;
	int check = x < WIDTH / 50 && y < HEIGHT / 50 && x >= 0 && y >= 0;
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
	int check = x < WIDTH / 50 && y < HEIGHT / 50 && x >= 0 && y >= 0;
	if (!check)
		return (-1);
	if (check && p->map[y][x] == '1')
		return (1);
	return (0);
}

void	ddah(t_player *p)
{
	// double dx = 50 / cos(degtorad(p->rayangle));
	double hx = 50, hy;
	t_point inc = get_hsign(p->rayangle);
	double x = floor(p->turnx / 50) * 50 + inc.x, y;
	hy = fabs(fabs(x - p->x) * tan(degtorad(p->rayangle)));
	y = p->turny + (hy * inc.signy);
	hy = fabs(50 * tan(degtorad(p->rayangle)));
	double tx, ty;
	// int clr[2] =  {ORANGE, GREEN};
	int i = 0;
	tx = p->x;
	ty = p->y;
	int k = 0;
	while (!is_wallh(p, x / 50, y / 50))
	{
		// draw_line(tx, ty, x, y, clr[i], p);
		tx = x;
		ty = y;
		x += hx * inc.signx;
		y += hy * inc.signy;
		p->turnx = x;
		p->turny = y;
		i = (i == 0 ? 1 : 0);
		k = -1;
	}
	if (is_wallh(p, x / 50, y / 50) == 1)
	{
		p->turnx = x;
		p->turny = y;
		// draw_line(tx, ty, x, y, clr[i], p);
	}
}
void	ddav(t_player *p)
{
	// double dx = 50 / sin(degtorad(p->rayangle));
	double hx, hy = 50;
	t_point inc = get_vsign(p->rayangle);
	double y = floor(p->y / 50) * 50 + inc.y, x;
	hx = fabs(fabs(p->y - y) / tan(degtorad(p->rayangle)));
	x = p->x + (hx * inc.signx);
	hx = fabs(50 / tan(degtorad(p->rayangle)));
	double tx, ty;
	// int clr[2] =  {YELLOW, RED};
	int i = 0;
	tx = p->x;
	ty = p->y;
	int k = 0;
	while (!is_wallv(p, x / 50, y / 50))
	{
		// draw_line(tx, ty, x, y, clr[i], p);
		tx = x;
		ty = y;
		x += hx * inc.signx;
		y += hy * inc.signy;
		p->turnx = x;
		p->turny = y;
		i = (i == 0 ? 1 : 0);
		k = -1;
	}
	if (is_wallv(p, x / 50, y / 50) == 1)
	{
		p->turnx = x;
		p->turny = y;
		// draw_line(tx, ty, x, y, clr[i], p);
	}
}

double	get_dis(double stx, double sty, double endx, double endy)
{
	return (sqrt(pow(endx - stx, 2) + pow(endy - sty, 2)));
}

void	dda(t_player *p)
{
	t_point hor;
	t_point ver;
	double dish, disv;
	ddah(p);
	hor.x = p->turnx;
	hor.y = p->turny;
	ddav(p);
	ver.x = p->turnx;
	ver.y = p->turny;
	dish = get_dis(p->x, p->y, hor.x, hor.y);
	disv = get_dis(p->x, p->y, ver.x, ver.y);
	if (dish == 0)
		dish = 10000;
	if (disv == 0)
		disv = 10000;
	p->turnx = dish > disv ? ver.x : hor.x;
	p->turny = dish > disv ? ver.y : hor.y;
}