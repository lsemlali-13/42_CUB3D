/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:31:11 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/13 21:47:50 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*-------------- COLLOR -------------------------*/

void	free_collor(char **stock1, char **stock2)
{
	int	i;

	i = 0;
	while (stock1[i])
	{
		free(stock1[i]);
		i++;
	}
	free(stock1);
	i = 0;
	while (stock2[i])
	{
		free(stock2[i]);
		i++;
	}
	free(stock2);
}

void	hndl_collore(t_game *game, int i)
{
	char	**stock1;
	char	**stock2;

	if (game->map_contant[i][0] == 'F' && game->map_contant[i][1] == ' ')
	{
		stock1 = ft_split(game->map_contant[i], ' ');
		stock2 = ft_split(stock1[1], ',');
		game->map->floor_color.r = ft_atoi(stock2[0]);
		game->map->floor_color.g = ft_atoi(stock2[1]);
		game->map->floor_color.b = ft_atoi(stock2[2]);
	}
	else if (game->map_contant[i][0] == 'C' && game->map_contant[i][1] == ' ')
	{
		stock1 = ft_split(game->map_contant[i], ' ');
		stock2 = ft_split(stock1[1], ',');
		game->map->ceilling_color.r = ft_atoi(stock2[0]);
		game->map->ceilling_color.g = ft_atoi(stock2[1]);
		game->map->ceilling_color.b = ft_atoi(stock2[2]);
	}
	else
		ft_error("collors error\n");
	free_collor(stock1, stock2);
}

/*-------------- TEXTUR -------------------------*/

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
		reture = ft_strdup(stock[1]);
		free_textur(stock);
		return(reture);
	}
	else
		ft_error("error in texture\n");
	return(NULL);
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

/*-------------- ALL_PROCECE -------------------------*/

void	handl_element(t_game *game, int i)
{
	if (game->map_contant[i][0] == 'F' || game->map_contant[i][0] == 'C')
		hndl_collore(game, i);
	else
		hndl_textur(game, i);
}

int	collect_element(t_game *game)
{
	int	i;
	int	element;

	i = 0;
	element = 0;
	game->map->textur = malloc(sizeof(t_textur));
	while (game->map_contant[i] && element < 6)
	{
		if (!game->map_contant[i][0])
			i++;
		else if (game->map_contant[i][0] == 'N' || game->map_contant[i][0] == 'S'
			|| game->map_contant[i][0] ==  'W' || game->map_contant[i][0] == 'E'
			|| game->map_contant[i][0] == 'F' || game->map_contant[i][0] == 'C')
			handl_element(game, i);
		else
			ft_error("error in element\n");
		i++;
		element++;
	}
	printf("%d\n", i);
	return (i);
}