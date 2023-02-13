#include "../includes/cub3d.h"

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	t_map	*map;

	if (argc != 2)
		ft_error("executed as follows: ./cub3D maps/map/*.cub\n");
	game = malloc(sizeof(t_game));
	game->file_name = ft_strdup(argv[1]);
	ft_check_file(game);
	map_setting(game);
	// for (int j = 0; j < game->size; j++)
		// printf("%s\n", game->map_contant[j]);

	printf("NO :%s\n", game->map->textur->north_texture);
	printf("SO :%s\n", game->map->textur->south_texture);
	printf("WE :%s\n", game->map->textur->west_texture);
	printf("EA :%s\n", game->map->textur->east_texture);
	printf("CELER\n");
	printf("%d\n", game->map->ceilling_color.r);
	printf("%d\n", game->map->ceilling_color.g);
	printf("%d\n", game->map->ceilling_color.b);
	printf("FLLOR\n");
	printf("%d\n", game->map->floor_color.r);
	printf("%d\n", game->map->floor_color.g);
	printf("%d\n", game->map->floor_color.b);

	for(int v = 0; v <= game->map->height; v++)
		printf("%s\n", game->map->map[v]);

	printf("START POSITION: %c(x=%d, y=%d)\n", game->map->starting_pos, game->map->player.x, game->map->player.y);
	// system("leaks cub3d");
	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, 500,
	// 		500, "cub3D_1337");
	// // xpm_to_img(&game);
	// // setting_img(game);
	// // collect_number(&game);
	// mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, exit_game, &game);
	// // mlx_key_hook(game.win, key_hook, &game);
	// mlx_loop(game.mlx);
	return (0);
}