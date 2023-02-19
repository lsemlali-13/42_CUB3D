#include "cub3d.h"

int draw_line(double x, double y, double toy, int color, t_img *p_img)
{	
	while (y < toy)
	{
		my_pixel_put(p_img, x, y, color);
		y++;
	}
	return (0);
}

int draw_texture(double x, double y, double toy, t_img *p_img, t_player *p, double wallh)
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
		color = get_color(&img, p->tox, roundf(newy));
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

	t_img *p_img;
	// t_point dst;
	p_img = malloc(sizeof(t_img));
	p_img->img = mlx_new_image(p->win->mlx_p, p->map_width, p->map_height);
	p_img->addr = mlx_get_data_addr(p_img->img, &(p_img->bits_per_pixel), &(p_img->line_length), &(p_img->endian));
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
		draw_line(i, 0, (p->map_height / 2) - wallh, BLUE, p_img);
		draw_texture(i, (p->map_height / 2) - wallh, (p->map_height / 2) + wallh, p_img, p, roundf((p->map_height / dis) * TILE_SIZE));
		draw_line(i, (p->map_height / 2) + wallh,  p->map_height - 1, BLACK, p_img);
		p->rayangle -= FOV / p->map_width;
	}
	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p_img->img, 0, 0);
}