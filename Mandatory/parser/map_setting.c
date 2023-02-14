/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:29 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/14 14:41:38 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/get_next_line.h"

int	get_file_size(char *filename)
{
	char	*line;
	int		size;
	int		fd;

	size = 0;
	fd = open(filename, O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		free(line);
		size++;
	}
	return (size - 1);
}

char	**read_map(t_game *game)
{
	char	**map_cont;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(game->file_name, O_RDONLY);
	if (fd <= 0)
		ft_error("error in opening file\n");
	game->size = get_file_size(game->file_name);
	line = get_next_line(fd);
	map_cont = malloc(sizeof(char *) * game->size + 1);
	while (line)
	{
		map_cont[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map_cont);
}

void	colect_playr_information(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	game->map->starting_pos = 0;
	while (game->map->map[++i] && i <= game->map->height)
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			if (game->map->map[i][j] != '1' && game->map->map[i][j] != ' '
				&& game->map->map[i][j] != '0')
			{
				if (game->map->starting_pos)
					ft_error("you mast have one playr!\n");
				else
				{
					game->map->starting_pos = game->map->map[i][j];
					game->map->player.x = j + 1;
					game->map->player.y = i + 1;
				}
			}
		}
	}
}

void	map_setting(t_game *game)
{
	int	index;

	index = 0;
	game->map = malloc(sizeof(t_map));
	game->map_contant = read_map(game);
	index = collect_element(game);
	check_texture(game->map->textur);
	collect_map(game, index);
	index = -1;
	while (++index < game->size)
		free(game->map_contant[index]);
	free(game->map_contant);
	check_map(game->map);
	colect_playr_information(game);
	if (!game->map->starting_pos)
		ft_error("playr not fond in map\n");
}

	// game->map->textur = get_texture(game);
	// index = get_collore(game);