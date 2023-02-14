/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:55:20 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/14 12:00:12 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	collect_map(t_game *game, int index)
{
	int	i;

	i = 0;
	while (!game->map_contant[index][0])
		index++;
	game->map->height = 0;
	while (game->map_contant[index + game->map->height][0]
		&& game->map->height + index < game->size - 1)
	{
		game->map->height++;
		if (game->map_contant[index + game->map->height][0] != '1'
			&& game->map_contant[index + game->map->height][0] != ' ')
			ft_error("error in map\n");
	}
	game->map->map = malloc(sizeof(char *) * (game->map->height + 1));
	while (game->map_contant[index] && index < game->size)
		game->map->map[i++] = ft_strdup(game->map_contant[index++]);
}
