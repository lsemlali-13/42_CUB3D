/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:31:14 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/21 15:36:33 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	main(int argc, char *argv[])
{
	t_game	*game;

	game = parsing(argc, argv);
	cast_rend(game->map);
	return (0);
}
