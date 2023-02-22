/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:18:03 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/22 13:16:49 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	textur_extention(char *str)
{
	int	n;

	n = ft_strlen(str);
	if (str[n - 4] == '.' && str[n - 3] == 'x'
		&& str[n - 2] == 'p'
		&& str[n - 1] == 'm')
		return ;
	ft_error("error in textur extantion\n");
}

void	check_existing(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_error("error in textur files\n");
	}
	close(fd);
}

void	free_textur(char **stock1)
{
	int	i;

	i = 0;
	while (stock1[i])
	{
		free(stock1[i]);
		i++;
	}
	free(stock1);
}

char	*getere(t_game *game, char *what, int go)
{
	char	**stock;
	char	*reture;

	stock = ft_split(game->map_contant[go], ' ', &go);
	if (ft_strncmp(stock[0], what, ft_strlen(stock[0])) == 0 && stock[1])
	{
		if (stock[2])
			ft_error("error in textur\n");
		reture = ft_strdup(stock[1]);
		free_textur(stock);
		return (reture);
	}
	else
		ft_error("error in texture\n");
	return (NULL);
}

void	hndl_textur(t_game *game, int i)
{
	if (game->map_contant[i][0] == 'N')
		game->map->textur->north_texture = getere(game, "NO", i);
	else if (game->map_contant[i][0] == 'S')
		game->map->textur->south_texture = getere(game, "SO", i);
	else if (game->map_contant[i][0] == 'W')
		game->map->textur->west_texture = getere(game, "WE", i);
	else if (game->map_contant[i][0] == 'E')
		game->map->textur->east_texture = getere(game, "EA", i);
}
