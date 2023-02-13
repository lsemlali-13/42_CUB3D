#include "../../includes/cub3d.h"

void	free_textur(char **stock1)
{
	int	i;

	i = 0;
	while (stock1[i])
	{
		free(stock1[i]);
		i++;
	}
	free(stock1);
}

void	check_texture(t_map *map)
{
	// check textures files is exixt
}

char	*getere(t_game *game, char *what, int go)
{
	char	**stock;
	char	*reture;

	stock = ft_split(game->map_contant[go], ' ');
	if (ft_strncmp(stock[0], what, ft_strlen(stock[0])) == 0 && stock[1])
	{
		reture = ft_strdup(stock[1]);
		free_textur(stock);
		return(reture);
	}
	else
		ft_error("error in texture\n");
	return(NULL);
}

t_textur	*get_texture(t_game *game)
{
	t_textur	*textur;
	int			i;

	i = 0;
	textur = malloc(sizeof(t_textur));
	while (game->map_contant && i < 4)
	{
		if (game->map_contant[i][0] == 'N')
			textur->north_texture = getere(game, "NO", i);
		else if (game->map_contant[i][0] == 'S')
			textur->south_texture = getere(game, "SO", i);
		else if (game->map_contant[i][0] == 'W')
			textur->west_texture = getere(game, "WE", i);
		else if (game->map_contant[i][0] == 'E')
			textur->east_texture = getere(game, "EA", i);
		else
			ft_error("error in texture\n");
		i++;
	}
	// check_texture(game->map);
	return (textur);
}