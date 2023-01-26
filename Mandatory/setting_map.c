#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

int	get_map_size(char *filename)
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

void	read_map(char *filename, t_game *game)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		ft_error("error in opening file\n");
	game->map.size = get_map_size(filename);
	line = get_next_line(fd);
	game->height = 0;
	game->width = ft_strlen(line);
	game->map_contant = malloc(sizeof(char*) * game->map.size);
	i = 0;
	game->map_contant[i] = ft_strdup(line);
	free(line);
	while (line)
	{
		game->height++;
		line = get_next_line(fd);
		if (line)
		{
			i++;
			game->map_contant[i] = ft_strdup(line);
			free(line);
		}
	}
	close(fd);
}

// void	read_map(char *filename, t_game *game)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	fd = open(filename, O_RDONLY);
// 	if (fd <= 0)
// 		ft_error("error in opening file\n");
// 	game->map.size = get_map_size(filename);
// 	line = get_next_line(fd);
// 	game->height = 0;
// 	game->width = ft_strlen(line);
// 	game->map_contant = malloc(sizeof(char*) * game->map.size);
// 	i = 0;
// 	game->map_contant[i] = ft_strdup(line);
// 	// check_first_line(game->line);
// 	free(line);
// 	while (line)
// 	{
// 		game->height++;
// 		line = get_next_line(fd);
// 		if (line)
// 		{
// 			i++;
// 			// check_inside_map(game->line);
// 			game->map_contant[i] = ft_strdup(line);
// 			free(line);
// 		}
// 	}

// 	// check_last_line(game);
// 	close(fd);
// 	// check_map(game);
// }
