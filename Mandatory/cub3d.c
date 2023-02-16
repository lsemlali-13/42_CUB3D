/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:31:14 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/16 17:14:34 by rarahhal         ###   ########.fr       */
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

// int color = 0xABCDEF;
// if (image->bits_per_pixel != 32)
//     color = mlx_get_color_value(windo->mlx, color);

int 	counter = 0;

for(int y = 0; y < 300; ++y)
{
for(int x = 0; x < 200; ++x)
{
    int pixel = (y * image->bits_per_pixel) + (x * 4);
	int color = (int)image->adr[pixel];

    if (image->endian == 1)        // Most significant (Alpha) byte first
    {
		printf("------- 1--------\n");
		// color = create_trgb(image->adr[pixel + 3], image->adr[pixel + 2], image->adr[pixel + 1], image->adr[pixel + 0]);
        image->adr[pixel + 0] = (color >> 24);
        image->adr[pixel + 1] = (color >> 16) & 0xFF;
        image->adr[pixel + 2] = (color >> 8) & 0xFF;
        image->adr[pixel + 3] = (color) & 0xFF;
    }
    else if (image->endian == 0)   // Least significant (Blue) byte first
    {
		printf("------- 2--------\n");
		// color = create_trgb(image->adr[pixel + 0], image->adr[pixel + 1], image->adr[pixel + 2], image->adr[pixel + 3]);
        image->adr[pixel + 0] = (color) & 0xFF;
        image->adr[pixel + 1] = (color >> 8) & 0xFF;
        image->adr[pixel + 2] = (color >> 16) & 0xFF;
        image->adr[pixel + 3] = (color >> 24);
    }
	// mlx_put_image_to_window(windo->mlx, windo->win, windo->image, 0, 0);
	mlx_pixel_put(windo->mlx, windo->win, y, x, (int)image->adr[counter++]);
	// image->adr += 4;
}
}
// for(int y = 0; y < 100; ++y)
// {	
// for(int x = 0; x < 200; ++x)
// {


//     int pixel = (int)*image->adr + (y * image->size_line + x * (image->bits_per_pixel / 8));
// 	mlx_pixel_put(windo->mlx, windo->win, y, x, (int)image->adr[pixel]);
// }
// }	
	
	// for (int i = 0; i < windo->image->size_line; i++)
	// 	mlx_pixel_put(windo->mlx, windo->win, 4, i, 0x0000FF00);
	
	// printf("%d\n", windo->image->adr);
	mlx_hook(windo->win, X_EVENT_KEY_EXIT, 0, exit_game, windo);
	// mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(windo->mlx);
	// free_main(game);
	return (0);
}









	// https://github.com/say10co/Cube3d_
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