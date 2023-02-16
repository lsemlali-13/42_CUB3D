/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:20:11 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/16 13:36:09 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
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

typedef struct s_image
{
	void	*img;
	char	*adr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		img_h;
	int		img_w;
}	t_image;


typedef struct s_textur
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
}	t_textur;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_map
{
	char		**map;
	int			height;
	t_textur	*textur;
	char		starting_pos;
	t_color		*floor_color;
	t_color		*ceilling_color;
	t_vector	player;

}	t_map;

typedef struct s_windo
{
	void	*win;
	void	*mlx;
	t_image	*image;
}	t_windo;


typedef struct s_game
{
	char	**map_contant;
	int		size;
	char	*file_name;
	t_map	*map;
}	t_game;

// libft
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*get_next_line_2(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
void	ft_putnbr(int n);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);


// parser Function
void	ft_check_file(t_game *game);
void	ft_error(char *error);
void	map_setting(t_game *game);
int		collect_element(t_game *game);
void	hndl_collore(t_game *game, int i);
void	hndl_textur(t_game *game, int i);
void	check_texture(t_textur *textur);
void	collect_map(t_game *game, int index);
void	check_map(t_map *map);
// t_textur	*get_texture(t_game *game);
// int			get_collore(t_game *game);

#endif