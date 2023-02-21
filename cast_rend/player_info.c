/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:33:52 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/20 13:28:36 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

void	get_player_pos(t_player *p, int c, int i, int j)
{
	if (c == 'E')
		p->rotangle = 0;
	if (c == 'N')
		p->rotangle = 90;
	if (c == 'W')
		p->rotangle = 180;
	if (c == 'S')
		p->rotangle = 270;
	p->x = (j * TILE_SIZE) + TILE_SIZE / 2;
	p->y = (i * TILE_SIZE) + TILE_SIZE / 2;
	p->tox = p->x;
	p->toy = p->y;
}

void	get_player_info(char **map, t_player *p)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E' || map[i][j] == 'S')
				get_player_pos(p, map[i][j], i, j);
			j++;
		}
		i++;
	}
	p->map_height = i * TILE_SIZE;
}
