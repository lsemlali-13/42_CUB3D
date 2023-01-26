#ifndef CUB3D_H
#define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


# define X_EVENT_KEY_EXIT       17

# define KEY_ESC    65307
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_vector
{
	int	x;
	int	y;
} t_vector;

// typedef struct texture
// {
	
// };	


typedef struct s_map
{
	char		**map;
	int			size;
	int			raw;
	int			col;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*file_name;
	char		*starting_pos;
	t_color		floor_color;
	t_color		ceilling_color;
	t_vector	player;

} t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
	char	**map_contant;
	t_map	map;
	// void	*img_player;
	// void	*img_exit;
	// void	*img_coll;
	// void	*img_space;
	// void	*img_wall;
	// int		img_height;
	// int		img_width;
	// char	*map_len;
	// int		all_coll;
	// int		coll_cnt;
	// int		walk_cnt;
	int		fd;
	char	*line;
	char	*fr;
}	t_game;

// libft
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*get_next_line_2(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
void	ft_putnbr(int n);

// helper Function
void	read_map(char *filename, t_game *game);
void	ft_error(char *error);

// map error
void	check_first_line(char *line);
void	check_inside_map(char *line);
void	check_last_line(t_game *game);
void	check_map(t_game *game);
void	ft_check_file(char *str, t_game *game);

#endif