#include "cub3d.h"

int draw_line(double x, double y, double toy, int color, t_img p_img)
{	
	while (y < toy)
	{
		my_pixel_put(p_img, x, y, color);
		y++;
	}
	return (0);
}

int draw_texture(double x, double y, double toy, t_img p_img, t_player *p, double wallh)
{
	double newy;
	int color;
	t_img	img;

	img = get_wich(p);
	newy = 0;
	double inc = img.h / (2 * wallh);
	p->tox = floor((int)(img.w * ((p->tox + p->toy) / TILE_SIZE)) % img.w);
	if ((2 * wallh) > p->map_height)
		newy = (int)((((2 * wallh) - p->map_height) / 2) * inc) % img.h;
	while (y < toy)
	{
		color = get_color(img, p->tox, newy);
		my_pixel_put(p_img, x, y, color);
		y++;
		newy += inc;
		if (newy > img.h)
			newy = (int)newy % img.h;
	}
	return (0);
}

void	ren3d(t_player *p)
{
	p->rayangle = p->rotangle + (FOV / 2);

	// t_point dst;
	for (int i = 0; i < p->map_width; i++)
	{
		p->tox = p->x;
		p->toy = p->y;
		dda(p);
		double dis = sqrt(pow(p->x - p->tox, 2.0) + pow(p->y - p->toy, 2.0));
		dis = dis * cos(degtorad(p->rayangle - p->rotangle));
		double wallh = roundf((p->map_height / dis) * TILE_SIZE);
		if (wallh > p->map_height / 2)
			wallh = p->map_height / 2;
		draw_line(i, 0, (p->map_height / 2) - wallh, BLUE, p->wind);
		draw_texture(i, (p->map_height / 2) - wallh, (p->map_height / 2) + wallh, p->wind, p, roundf((p->map_height / dis) * TILE_SIZE));
		draw_line(i, (p->map_height / 2) + wallh,  p->map_height - 1, BLACK, p->wind);
		p->rayangle -= FOV / p->map_width;
	}
	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->wind.img, 0, 0);
}