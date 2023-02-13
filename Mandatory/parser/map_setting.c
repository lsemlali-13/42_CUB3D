#include "../../includes/cub3d.h"
#include "../../includes/get_next_line.h"

int	get_file_size(char *filename)
{
	char	*line;
	int		size;
	int		fd;

	size = 0;
	fd = open(filename, O_RDONLY);
	while(line)
	{
		line = get_next_line(fd);
		size++;
	}
	return(size - 1);
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
	map_cont = malloc(sizeof(char*) * game->size + 1);
	map_cont[i] = ft_strdup(line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			i++;
			map_cont[i] = ft_strdup(line);
			free(line);
		}
	}
	close(fd);
	return (map_cont);
}

void	colect_playr_information(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->map[i] && i <= game->map->height)
	{
		j = 0;
		while (game->map->map[i][j])
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
			j++;
		}
		i++;
	}
	if (!game->map->starting_pos)
		ft_error("playr not fond in map\n");
}

void	map_setting(t_game *game)
{
	int index;

	game->map = malloc(sizeof(t_map));
	game->map_contant = read_map(game);
	game->map->textur = get_texture(game);
	index = get_collore(game);
	collect_map(game, index);
	check_map(game->map);
	colect_playr_information(game);
}
