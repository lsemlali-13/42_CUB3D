#ifndef CUB3D_H
# define CUB3D_H

# define FOV 66
# define SPEED 5
# define WIDTH 3000
# define HEIGHT 1000


# define UPR 1
# define UPL -1
# define DOWNR 0
# define DOWNL -2
# define UP 13
# define DOWN 1
# define RIGHT 2
# define LEFT 0
# define ROTR 124
# define ROTL 123

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
# include "mlx/mlx.h"

typedef struct s_point
{
	double x;
	double signx;
	double y;
	double signy;
}	t_point;

typedef struct s_img{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef struct s_win{
	void	*mlx_p;
	void	*mlx_w;
	void	*img_0;
	void	*img_1;
	void	*img_p;
	int		height;
	int		width;
} t_win;

typedef struct s_player{
	t_win	*win;
	char	**map;
	void	*img;
	double		turnx;
	double		turny;
	double 		rotangle;
	double		rayangle;
	int		x_idx;
	int		y_idx;
	double		x;
	double		y;
	int			checkh;	
	int			checkv;	
	int			height;
	int			width;
	int			map_height;
	int			map_width;
} t_player;


char	**ft_split(char const *s, char c);
void	dda(t_player *p);
double	degtorad(double ang);

#endif