#include <mlx.h>

# define WIDTH 500
# define HEIGHT 300

int main()
{
	void    *win;
	void	*p;
	int			fd;
	char		**map;

	p = mlx_init();
	win = mlx_new_window(p, WIDTH, HEIGHT, "CUB3D");
	int w = 4291, h = 2861;
	void    img = mlx_xpm_file_to_image(p->win->mlx_p, "image.xpm", &w, &h);
	p->img.addr = mlx_get_data_addr(p->img.img, &(p->img.bits_per_pixel), &(p->img.line_length), &(p->img.endian));
	get_player_info(map, p);
	ren3d(p);
	mlx_hook(win->mlx_w, 2, 0, key_hook, p);
	mlx_loop(win->mlx_p);
}