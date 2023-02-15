/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:31:14 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/15 21:29:38 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	free(game->map->ceilling_color);
	free(game->map->floor_color);
	free(game->map);
	free(game);
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	t_map	*map;
	// t_image	*image;

	if (argc != 2)
		ft_error("executed as follows: ./cub3D maps/map/*.cub\n");
	game = malloc(sizeof(t_game));
	// https://github.com/say10co/Cube3d_
	// image = malloc(sizeof(t_image));
	game->file_name = ft_strdup(argv[1]);
	ft_check_file(game);
	map_setting(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 500,
			500, "cub3D_1337");
	// image->img = mlx_xpm_file_to_image(game->mlx, game->map->textur->north_texture, &image->img_w, &image->img_h);
	// image->adr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->size_line, &image->endian);
	// printf("%d\n", image->size_line);
	mlx_hook(game->win, X_EVENT_KEY_EXIT, 0, exit_game, game);
	// mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game->mlx);
	// free_main(game);
	return (0);
}
	// printf("SO :%s\n", game->map->textur->south_texture);
	// printf("WE :%s\n", game->map->textur->west_texture);
	// printf("NO :%s\n", game->map->textur->north_texture);
	// printf("EA :%s\n", game->map->textur->east_texture);
	// printf("CELER\n");
	// printf("%d\n", game->map->ceilling_color->r);
	// printf("%d\n", game->map->ceilling_color->g);
	// printf("%d\n", game->map->ceilling_color->b);
	// printf("FLLOR\n");
	// printf("%d\n", game->map->floor_color->r);
	// printf("%d\n", game->map->floor_color->g);
	// printf("%d\n", game->map->floor_color->b);
	// for(int v = 0; v <= game->map->height; v++)
	// 	printf("%s\n", game->map->map[v]);
	// printf("START POSITION: %c(x=%d, y=%d)\n", game->map->starting_pos,
	// 	game->map->player.x, game->map->player.y);