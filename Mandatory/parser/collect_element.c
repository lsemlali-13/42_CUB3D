/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:31:11 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/14 11:54:31 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		else if (game->map_contant[i][0] == 'N'
			|| game->map_contant[i][0] == 'S'
			|| game->map_contant[i][0] == 'W'
			|| game->map_contant[i][0] == 'E'
			|| game->map_contant[i][0] == 'F'
			|| game->map_contant[i][0] == 'C')
		{
			handl_element(game, i);
			i++;
			element++;
		}
		else
			ft_error("error in element\n");
	}
	return (i);
}
