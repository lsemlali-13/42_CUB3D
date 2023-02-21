/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:31:14 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/20 15:34:09 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// while true ; do leaks minishell ; sleep 1 ; done ;
void	free_main(t_game *game)
{
	free(game->file_name);
	free(game->map->textur->north_texture);
	free(game->map->textur->south_texture);
	free(game->map->textur->west_texture);
	free(game->map->textur->east_texture);
	free(game->map->textur);
	while (game->map->height > 0)
		free(game->map->map[game->map->height] - 1);
	free(game->map->map);
	free(game->map);
	free(game);
}

t_game	*parsing(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		ft_error("executed as follows: ./cub3D maps/map/*.cub\n");
	game = malloc(sizeof(t_game));
	game->file_name = ft_strdup(argv[1]);
	ft_check_file(game);
	map_setting(game);
	return (game);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	// t_windo	*windo;
	// t_image	*image;

	game = parsing(argc, argv);
	cast_rend(game->map);
	free_main(game);
	return (0);
}


