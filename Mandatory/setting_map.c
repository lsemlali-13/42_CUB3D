#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

void	map_read(char *filename, t_game *game)
{
	game->fd = open(filename, O_RDONLY);
	if (game->fd <= 0)
		ft_error("error in opening file\n");
	game->line = get_next_line(game->fd);
	game->height = 0;
	game->width = ft_strlen(game->line);
	game->map_len = ft_strdup(game->line);
	check_first_line(game->line);
	free(game->line);
	while (game->line)
	{
		game->height++;
		game->line = get_next_line(game->fd);
		if (game->line)
		{
			game->fr = game->map_len;
			check_inside_map(game->line);
			game->map_len = ft_strjoin(game->fr, game->line);
			free(game->line);
			free(game->fr);
		}
	}
	check_last_line(game);
	close(game->fd);
	check_map(game);
}
