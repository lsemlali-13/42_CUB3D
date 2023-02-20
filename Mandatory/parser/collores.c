/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collores.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:00:34 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/20 12:31:56 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	if (i > 3)
		ft_error("error in colors\n");
	free(stock2);
}

// t_color	*help(t_game *game, t_color *collor, int i)
// {
// 	char	**stock1;
// 	char	**stock2;

// 	collor = malloc(sizeof(t_color));
// 	collor->r = 0;
// 	collor->g = 0;
// 	collor->b = 0;
// 	stock1 = ft_split(game->map_contant[i], ' ');
// 	stock2 = ft_split(stock1[1], ',');
// 	if (!stock2[0] || !stock2[1] || !stock2[2])
// 		ft_error("error in collores\n");
// 	collor->r = ft_atoi(stock2[0]);
// 	collor->g = ft_atoi(stock2[1]);
// 	collor->b = ft_atoi(stock2[2]);
// 	free_collor(stock1, stock2);
// 	return (collor);
// }

// void	hndl_collore(t_game *game, int i)
// {
// 	if (game->map_contant[i][0] == 'F' && game->map_contant[i][1] == ' ')
// 		game->map->floor_color = help(game, game->map->floor_color, i);
// 	else if (game->map_contant[i][0] == 'C' && game->map_contant[i][1] == ' ')
// 		game->map->ceilling_color = help(game, game->map->ceilling_color, i);
// 	else
// 		ft_error("collors error\n");
// }

int	rgb_to_dec(int r, int g, int b)
{
	int	color;
	
	color = 0;
	color += r << 16;
	color += g << 8;
	color += b;
	return (color);
}

int	help(t_game *game, int i)
{
	char	**stock1;
	char	**stock2;
	int		color;

	stock1 = ft_split(game->map_contant[i], ' ');
	stock2 = ft_split(stock1[1], ',');
	if (!stock2[0] || !stock2[1] || !stock2[2])
		ft_error("error in collores\n");
	color = rgb_to_dec(ft_atoi(stock2[0]), ft_atoi(stock2[1]), ft_atoi(stock2[2]));
	free_collor(stock1, stock2);
	return (color);
}

void	hndl_collore(t_game *game, int i)
{
	if (game->map_contant[i][0] == 'F' && game->map_contant[i][1] == ' ')
		game->map->floor_color = help(game, i);
	else if (game->map_contant[i][0] == 'C' && game->map_contant[i][1] == ' ')
		game->map->ceilling_color = help(game, i);
	else
		ft_error("collors error\n");
}

// void	free_collor(char **stock1, char **stock2)
// {
// 	int	i;

// 	i = 0;
// 	while (stock1[i])
// 	{
// 		free(stock1[i]);
// 		i++;
// 	}
// 	free(stock1);
// 	i = 0;
// 	while (stock2[i])
// 	{
// 		free(stock2[i]);
// 		i++;
// 	}
// 	free(stock2);
// }

// int	get_collore(t_game *game)
// {
// 	char	**stock1;
// 	char	**stock2;
// 	int		i;
// 	int		stop;

// 	i = 4;
// 	while (!game->map_contant[i][0])
// 		i++;
// 	stop = i + 2;
// 	while (game->map_contant[i] && i < stop)
// 	{
// 		if (game->map_contant[i][0] == 'F' && game->map_contant[i][1] == ' ')
// 		{
// 			stock1 = ft_split(game->map_contant[i], ' ');
// 			stock2 = ft_split(stock1[1], ',');
// 			game->map->floor_color.r = ft_atoi(stock2[0]);
// 			game->map->floor_color.g = ft_atoi(stock2[1]);
// 			game->map->floor_color.b = ft_atoi(stock2[2]);
// 		}
// 		else if (game->map_contant[i][0] == 'C'
			// && game->map_contant[i][1] == ' ')
// 		{
// 			stock1 = ft_split(game->map_contant[i], ' ');
// 			stock2 = ft_split(stock1[1], ',');
// 			game->map->ceilling_color.r = ft_atoi(stock2[0]);
// 			game->map->ceilling_color.g = ft_atoi(stock2[1]);
// 			game->map->ceilling_color.b = ft_atoi(stock2[2]);
// 		}
// 		else
// 			ft_error("collors error\n");
// 		i++;
// 		free_collor(stock1, stock2);
// 	}
// 	return (i);
// }