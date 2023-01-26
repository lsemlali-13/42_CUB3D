#ifndef CUB3D_H
# define CUB3D_H

# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include "mlx/mlx.h"

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
	int		x_idx;
	int		y_idx;
	int		x;
	int		y;
	int		height;
	int		width;
} t_player;


char	**ft_split(char const *s, char c);

#endif