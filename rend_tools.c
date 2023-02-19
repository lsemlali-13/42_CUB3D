#include "cub3d.h"

int	get_color(t_img data, int x, int y)
{
	char *dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	my_pixel_put(t_img data, int x, int y, int color)
{
	char *dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_img	get_wich(t_player *p)
{
	if (p->which_tex == 'E')
		return (p->img_e);
	if (p->which_tex == 'N')
		return (p->img_n);
	if (p->which_tex == 'W')
		return (p->img_w);
	return (p->img_s);
}