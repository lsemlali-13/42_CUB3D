/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:43:48 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/21 12:58:16 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

int	draw_line(t_point fr, double toy, int color, t_img p_img)
{	
	while (fr.y < toy)
	{
		my_pixel_put(p_img, fr.x, fr.y, color);
		(fr.y)++;
	}
	return (0);
}

int	draw_texture(t_point fr, t_img p_img, t_player *p, double wallh)
{
	t_img	img;
	double	newy;
	double	inc;
	int		color;

	img = get_wich(p);
	newy = 0;
	inc = img.h / (2 * wallh);
	p->tox = floor((int)(img.w * ((p->tox + p->toy) / TILE_SIZE)) % img.w);
	if ((2 * wallh) > p->win_height)
		newy = (int)((((2 * wallh) - p->win_height) / 2) * inc) % img.h;
	p->toy = (p->win_height / 2) + ((p->win_height / 2) - fr.y);
	while (fr.y < p->toy)
	{
		color = get_color(img, p->tox, newy);
		my_pixel_put(p_img, fr.x, fr.y, color);
		(fr.y)++;
		newy += inc;
		if (newy > img.h)
			newy = (int)newy % img.h;
	}
	return (0);
}

void	draw(t_player *p, double wallh, double dis, int i)
{
	t_point	from;

	from.x = i;
	from.y = 0;
	draw_line(from, (p->win_height / 2) \
		- wallh, p->map->ceilling_color, p->wind);
	from.y = (p->win_height / 2) - wallh;
	draw_texture(from, p->wind, p, \
		roundf((p->win_height / dis) * TILE_SIZE));
	from.y = (p->win_height / 2) + wallh;
	draw_line(from, p->win_height - 1, p->map->floor_color, p->wind);
}

void	ren3d(t_player *p)
{
	double	dis;
	double	wallh;
	int		i;

	p->rayangle = p->rotangle + (FOV / 2);
	i = 0;
	while (i < p->win_width)
	{
		p->tox = p->x;
		p->toy = p->y;
		dda(p);
		dis = sqrt(pow(p->x - p->tox, 2.0) + pow(p->y - p->toy, 2.0));
		dis = dis * cos(degtorad(p->rayangle - p->rotangle));
		wallh = roundf(((p->win_height) / dis) * TILE_SIZE);
		if (wallh > p->win_height / 2)
			wallh = p->win_height / 2;
		draw(p, wallh, dis, i);
		p->rayangle -= FOV / p->win_width;
		i++;
	}
	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->wind.img, 0, 0);
}
