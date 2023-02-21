/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:04:29 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/21 15:53:03 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

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

int	get_file_size(char *filename)
{
	char	*line;
	int		size;
	int		fd;

	size = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		size++;
	}
	return (size);
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
	map_cont = malloc(sizeof(char *) * (game->size + 1));
	while (line)
	{
		map_cont[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map_cont[i] = NULL;
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
