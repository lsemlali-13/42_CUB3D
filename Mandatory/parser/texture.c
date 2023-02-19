/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:18:03 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/14 15:09:36 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	check_texture(t_textur *textur)
{
	textur_extention(textur->north_texture);
	textur_extention(textur->south_texture);
	textur_extention(textur->west_texture);
	textur_extention(textur->east_texture);
	check_existing(textur->north_texture);
	check_existing(textur->south_texture);
	check_existing(textur->west_texture);
	check_existing(textur->east_texture);
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

	stock = ft_split(game->map_contant[go], ' ');
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

// void	free_textur(char **stock1)
// {
// 	int	i;

// 	i = 0;
// 	while (stock1[i])
// 	{
// 		free(stock1[i]);
// 		i++;
// 	}
// 	free(stock1);
// }

// char	*getere(t_game *game, char *what, int go)
// {
// 	char	**stock;
// 	char	*reture;

// 	stock = ft_split(game->map_contant[go], ' ');
// 	if (ft_strncmp(stock[0], what, ft_strlen(stock[0])) == 0 && stock[1])
// 	{
// 		reture = ft_strdup(stock[1]);
// 		free_textur(stock);
// 		return(reture);
// 	}
// 	else
// 		ft_error("error in texture\n");
// 	return(NULL);
// }

// t_textur	*get_texture(t_game *game)
// {
// 	t_textur	*textur;
// 	int			i;

// 	i = 0;
// 	textur = malloc(sizeof(t_textur));
// 	while (game->map_contant && i < 4)
// 	{
// 		if (game->map_contant[i][0] == 'N')
// 			textur->north_texture = getere(game, "NO", i);
// 		else if (game->map_contant[i][0] == 'S')
// 			textur->south_texture = getere(game, "SO", i);
// 		else if (game->map_contant[i][0] == 'W')
// 			textur->west_texture = getere(game, "WE", i);
// 		else if (game->map_contant[i][0] == 'E')
// 			textur->east_texture = getere(game, "EA", i);
// 		else
// 			ft_error("error in texture\n");
// 		i++;
// 	}
// 	// check_texture(game->map);
// 	return (textur);
// }