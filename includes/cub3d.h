/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:20:11 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/22 13:15:46 by lsemlali         ###   ########.fr       */
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
# define ESC       53

typedef struct s_textur
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
}	t_textur;

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
	int			floor_color;
	int			ceilling_color;
	t_vector	player;

}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map_contant;
	int		size;
	char	*file_name;
	t_map	*map;
}	t_game;

// libft
int		ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*get_next_line_2(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
void	ft_putnbr(int n);
char	**ft_split(char const *s, char c, int *k);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);

// parser Function
void	ft_check_file(t_game *game);
void	ft_error(char *error);
void	map_setting(t_game *game);
int		collect_element(t_game *game);
void	hndl_collore(t_game *game, int i);
void	hndl_textur(t_game *game, int i);
void	textur_extention(char *str);
void	check_existing(char *str);
void	collect_map(t_game *game, int index);
void	check_map(t_map *map);

// rendering 
void	cast_rend(t_map *map);

#endif