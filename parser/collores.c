/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collores.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:00:34 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/22 13:19:37 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	rgb_to_dec(int r, int g, int b)
{
	int	color;

	color = 0;
	color += r << 16;
	color += g << 8;
	color += b;
	return (color);
}

int	arr_s(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	help(t_game *game, int i)
{
	char	**stock1;
	char	**stock2;
	int		color;
	int		k;

	k = 0;
	stock1 = ft_split(game->map_contant[i], ' ', &k);
	if (arr_s(stock1) != 2)
		ft_error("error in collores\n");
	k = 0;
	stock2 = ft_split(stock1[1], ',', &k);
	if (arr_s(stock2) != 3 || k != 2)
		ft_error("error in collores\n");
	color = rgb_to_dec(ft_atoi(stock2[0]),
			ft_atoi(stock2[1]), ft_atoi(stock2[2]));
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
