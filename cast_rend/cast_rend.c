/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:33:49 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/22 11:27:01 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

int	exit_game(t_win *win)
{
	mlx_destroy_window(win->mlx_p, win->mlx_w);
	exit(0);
}

int	key_hook(int keycode, void *p)
{
	t_player	*pl;

	pl = (t_player *)p;
	if (keycode == ESC)
		exit_game(pl->win);
	move_player(keycode, pl);
	pl->mouseang = 0;
	return (0);
}

void	load_textures(t_player *p)
{
	p->img_e.img = mlx_xpm_file_to_image(p->win->mlx_p, \
		p->map->textur->east_texture, &p->img_e.w, &p->img_e.h);
	p->img_n.img = mlx_xpm_file_to_image(p->win->mlx_p, \
		p->map->textur->north_texture, &p->img_n.w, &p->img_n.h);
	p->img_w.img = mlx_xpm_file_to_image(p->win->mlx_p, \
		p->map->textur->west_texture, &p->img_w.w, &p->img_w.h);
	p->img_s.img = mlx_xpm_file_to_image(p->win->mlx_p, \
		p->map->textur->south_texture, &p->img_s.w, &p->img_s.h);
	if (!p->img_e.img || !p->img_n.img || !p->img_w.img || !p->img_s.img)
		ft_error("error in xpm files\n");
	p->img_e.addr = mlx_get_data_addr(p->img_e.img, &(p->img_e.bits_per_pixel), \
		&(p->img_e.line_length), &(p->img_e.endian));
	p->img_n.addr = mlx_get_data_addr(p->img_n.img, &(p->img_n.bits_per_pixel), \
		&(p->img_n.line_length), &(p->img_n.endian));
	p->img_w.addr = mlx_get_data_addr(p->img_w.img, &(p->img_w.bits_per_pixel), \
		&(p->img_w.line_length), &(p->img_w.endian));
	p->img_s.addr = mlx_get_data_addr(p->img_s.img, &(p->img_s.bits_per_pixel), \
		&(p->img_s.line_length), &(p->img_s.endian));
}

int	mouse_code(int x, int y, void *p)
{
	t_player	*pl;

	pl = (t_player *)p;
	(void)y;
	if (x > pl->mousex || (x == pl->mousex && x > pl->win_width / 2))
		pl->mouseang = -5;
	else
		pl->mouseang = +5;
	pl->mousex = x;
	return (0);
}

void	cast_rend(t_map *map)
{
	t_win		*win;
	t_player	*p;

	p = malloc(sizeof(t_player));
	win = malloc(sizeof(t_win));
	win->mlx_p = mlx_init();
	p->win = win;
	p->map = map;
	load_textures(p);
	get_player_info(map->map, p);
	p->win_width = 70 * TILE_SIZE;
	p->win_height = 30 * TILE_SIZE;
	win->mlx_w = mlx_new_window(win->mlx_p, \
		p->win_width, p->win_height, "CUB3D");
	p->wind.img = mlx_new_image(p->win->mlx_p, p->win_width, p->win_height);
	p->wind.addr = mlx_get_data_addr(p->wind.img, &(p->wind.bits_per_pixel), \
		&(p->wind.line_length), &(p->wind.endian));
	ren3d(p);
	mlx_hook(win->mlx_w, X_EVENT_KEY_EXIT, 0, exit_game, win);
	p->mouseang = 0;
	mlx_hook(win->mlx_w, 6, 0, mouse_code, p);
	mlx_key_hook(win->mlx_w, key_hook, p);
	p->mousex = 0;
	mlx_loop(win->mlx_p);
}
