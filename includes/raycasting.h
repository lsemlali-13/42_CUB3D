/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:28:27 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/22 13:17:19 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define FOV 66.66
# define SPEED 5
# define WIDTH 1500
# define HEIGHT 1200
# define TILE_SIZE 30

# define UPR 1
# define UPL -1
# define DOWNR 0
# define DOWNL -2
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define ROTR 100
# define ROTL 97

# define BLUE 0X0000FF
# define RED 0XFF0000
# define WHITE 0XFFFFFF
# define GREEN 0X00FF00

# define BLACK 0X000000
# define PURPLE 0X800080
# define ORANGE 0XFF5733
# define YELLOW 0XF4D03F

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "cub3d.h"

typedef struct s_point
{
	double	x;
	double	signx;
	double	y;
	double	signy;
}	t_point;

typedef struct s_img{
	void	*img;
	int		w;
	int		h;
	char	*addr;
	char	*dst;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_win{
	void	*mlx_p;
	void	*mlx_w;
	void	*img_0;
	void	*img_1;
	void	*img_p;
}	t_win;

typedef struct s_player{
	t_win		*win;
	t_map		*map;
	int			which_tex;
	double		tox;
	double		toy;
	double		rotangle;
	double		rayangle;
	double		x;
	double		mousex;
	double		mouseang;
	double		y;
	int			map_height;
	int			win_height;
	int			win_width;
	t_img		wind;
	t_img		img_e;
	t_img		img_n;
	t_img		img_w;
	t_img		img_s;
}	t_player;

void	dda(t_player *p);
double	degtorad(double ang);
int		is_wallh(t_player *p, int x, int y);
void	ren3d(t_player *p);
t_img	get_wich(t_player *p);
int		get_color(t_img data, int x, int y);
void	my_pixel_put(t_img data, int x, int y, int color);
void	move_player(int key, t_player *p);
void	get_player_info(char **map, t_player *p);
void	ddah(t_player *p);
void	ddav(t_player *p);

#endif
