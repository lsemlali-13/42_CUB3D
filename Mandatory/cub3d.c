/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:31:14 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/19 14:08:50 by rarahhal         ###   ########.fr       */
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
	free(game->map->ceilling_color);
	free(game->map->floor_color);
	free(game->map);
	free(game);
}

int	exit_game(t_windo *windo)
{
	mlx_destroy_window(windo->mlx, windo->win);
	exit(0);
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
	t_windo	*windo;
	t_image	*image;

	game = parsing(argc, argv);

	windo =  malloc(sizeof(t_windo));
	windo->image = malloc(sizeof(t_image));
	windo->mlx = mlx_init();
	windo->win = mlx_new_window(windo->mlx, 1000,
			1000, "cub3D_1337");
	windo->image->img_h = 600;
	windo->image->img_w = 500;
	windo->image->img = mlx_new_image(windo->mlx, windo->image->img_w, windo->image->img_h);
	windo->image->adr = mlx_get_data_addr(windo->image->img, &windo->image->bits_per_pixel, &windo->image->size_line, &windo->image->endian);

	image = malloc(sizeof(t_image));
	image->img = mlx_xpm_file_to_image(windo->mlx, "WALL.xpm", &image->img_w, &image->img_h);
	image->adr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->size_line, &image->endian);

	mlx_hook(windo->win, X_EVENT_KEY_EXIT, 0, exit_game, windo);
	mlx_loop(windo->mlx);
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