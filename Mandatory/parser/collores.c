#include "../../includes/cub3d.h"

int	get_collore(t_game *game)
{
	char	**stock1;
	char	**stock2;
	int		i;
	int		stop;

	i = 4;
	while (!game->map_contant[i][0])
		i++;
	stop = i + 2;
	while (game->map_contant[i] && i < stop)
	{
		if (game->map_contant[i][0] == 'F' && game->map_contant[i][1] == ' ')
		{
			stock1 = ft_split(game->map_contant[i], ' ');
			stock2 = ft_split(stock1[1], ',');
			game->map.floor_color.r = ft_atoi(stock2[0]);
			game->map.floor_color.g = ft_atoi(stock2[1]);
			game->map.floor_color.b = ft_atoi(stock2[2]);
		}
		else if (game->map_contant[i][0] == 'C' && game->map_contant[i][1] == ' ')
		{
			stock1 = ft_split(game->map_contant[i], ' ');
			stock2 = ft_split(stock1[1], ',');
			game->map.ceilling_color.r = ft_atoi(stock2[0]);
			game->map.ceilling_color.g = ft_atoi(stock2[1]);
			game->map.ceilling_color.b = ft_atoi(stock2[2]);
		}
		else
			ft_error("collors error\n");
		i++;
	}
	return (i);
}