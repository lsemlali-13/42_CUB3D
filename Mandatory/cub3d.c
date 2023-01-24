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
	ft_check_file(argv[1], &game);
	map_read(argv[argc - 1], &game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 500,
			500, "cub3D_1337");
	// xpm_to_img(&game);
	// setting_img(game);
	// collect_number(&game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, exit_game, &game);
	// mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}