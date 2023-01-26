#include "../includes/cub3d.h"

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
		ft_error("executed as follows: ./cub3D maps/map/*.cub\n");
	game.map.file_name = ft_strdup(argv[1]);   //free file_name in cas de exit !!! 
	ft_check_file(game.map.file_name, &game);
	read_map(game.map.file_name, &game);
	for (int j = 0; j < game.map.size; j++)
		printf("%s\n", game.map_contant[j]);
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