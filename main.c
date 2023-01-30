#include "cub3d.h"

double	degrees_to_radians(int fov)
{
	return (fov * M_PI / 180);
}

char	**read_map(int fd)
{
	char	s[1000];

	read(fd, s, 1000);
	return (ft_split(s, '\n'));
}

int draw_line(t_player *p, int tox, int toy, int color)
{
	double dx = tox - p->x;
	double dy = toy - p->y;
	int pxs = sqrt((dx * dx) + (dy * dy));
	dx /= pxs;
	dy /= pxs;
	double px = p->x;
	double py = p->y;
	while (pxs)
	{
		mlx_pixel_put(p->win->mlx_p, p->win->mlx_w, px, py, color);
		px += dx;
		py += dy;
		--pxs;
	}
	return (0);
}

void	ren3d(t_player *p)
{
	double ang = p->rotangle - FOV / 2;
	t_player tmp = *p;
	for (int i = 0; i < 1000; i++)
	{
		p->turnx = p->x;
		p->turny = p->y;
		while (p->map[(int)p->turny / 50][(int)p->turnx / 50] != '1')
		{
			p->turnx += cos(degrees_to_radians(ang));
			p->turny += sin(degrees_to_radians(ang));
		}
		double dis = sqrt(pow(p->x - p->turnx, 2) + pow(p->y - p->turny, 2));
		double wallh = (250 / dis) * 50;
		tmp.x = i;
		tmp.y = 0;
		draw_line(&tmp, i, 250 - wallh, BLUE);
		tmp.y = 250 - wallh;
		draw_line(&tmp, i, 250 + wallh, YELLOW);
		tmp.y = 250 + wallh;
		draw_line(&tmp, i, 500, RED);
		ang += 66.0 / 1000.0;
	}
}

// void draw_line(t_player *p, int x2, int y2) {
//     int dx = abs(x2 - p->x);
//     int dy = abs(y2 - p->y);
//     int x = p->x;
//     int y = p->y;
//     int sx = p->x < x2 ? 1 : -1;
//     int sy = p->y < y2 ? 1 : -1;
//     int err = dx - dy;

//     while ((x != x2 || y != y2) && p->map[y / 50][x / 50] != '1') {
//         mlx_pixel_put(p->win->mlx_p, p->win->mlx_w, x, y, 0x60ec1d); // put a white pixel at (x,y)
//         int e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y += sy;
//         }
//     }
//     mlx_pixel_put(p->win->mlx_p, p->win->mlx_w, x, y, 0x60ec1d); 
// }

// void	camera(t_player *p)
// {
// 	int k = p->turn;
// 	while (k < p->turn * 50)
// 	{
// 		draw_line(p, p->win->mlx_p, p->win->mlx_w, p->x, p->y, 0, k);
// 		k++;
// 	}
// 	p->turn += 50;
// }

void	create_wind(char **map, t_player *p)
{
	int i = 0;
	int j;
	int x = 0;
	int y = 0;

	while (map[i])
	{
		j = 0;
		x = 0;
		while (map[i][j])
		{
			// if (map[i][j] == '1')
			// 	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_1, x, y);
			if (map[i][j] == 'p')
			{
				p->x = x;
				p->y = y;
				p->x_idx = j;
				p->y_idx = i;
				p->rotangle = 0;
				p->turnx = x;
				p->turny = y;
				// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, x, y);
				// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, x, y);
			}
			// else {
			// 	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, x, y);
			// }
			j++;
			x += 50;
		}
		i++;
		y += 50;
	}
}

void	move_player(int key, t_player *p)
{
	if (key == UP && p->map[(p->y - 10) / 50][p->x_idx] != '1')
	{
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x += cos(degrees_to_radians(p->rotangle)) * 3;
		p->y += sin(degrees_to_radians(p->rotangle)) * 3;
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	if (key == DOWN && p->map[(p->y + 10) / 50][p->x_idx] != '1')
	{
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x -= cos(degrees_to_radians(p->rotangle)) * 3;
		p->y -= sin(degrees_to_radians(p->rotangle)) * 3;
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	if (key == RIGHT && p->map[p->y_idx][(p->x + 10) / 50] != '1')
	{
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x += sin(degrees_to_radians(p->rotangle)) * 3;
		p->y += cos(degrees_to_radians(p->rotangle)) * 3;
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	if (key == LEFT && p->map[p->y_idx][(p->x - 10) / 50] != '1')
	{
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x -= sin(degrees_to_radians(p->rotangle)) * 3;
		p->y -= cos(degrees_to_radians(p->rotangle)) * 3;
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	if (key == ROTR)
	{
		p->rotangle += 3;
		ren3d(p);
	}
	if (key == ROTL)
	{
		p->rotangle -= 3;
		ren3d(p);
	}
}

int	key_hook(int keycode, void *p)
{
	p = (t_player *)p;
	move_player(keycode, p);
	return (0);
}

int main()
{
	t_win		*win;
	t_player	*p;
	int			fd;
	char		**map;

	p = malloc(sizeof(t_player));
	p->height = 10;
	p->width = 10;
	win = malloc(sizeof(t_win));
	win->height = 50;
	win->width = 50;
	win->mlx_p = mlx_init();
	win->mlx_w = mlx_new_window(win->mlx_p, WIDTH, HEIGHT, "hello");
	win->img_0 = mlx_xpm_file_to_image(win->mlx_p, "textures/black.xpm", &win->height, &win->width);
	win->img_p = mlx_xpm_file_to_image(win->mlx_p, "textures/player.xpm", &p->height, &p->width);
	win->img_1 = mlx_xpm_file_to_image(win->mlx_p, "textures/gray.xpm", &win->height, &win->width);
	p->win = win;
	fd = open("maps/map.cub", O_RDWR);
	map = read_map(fd);
	p->map = map;
	create_wind(map, p);
	ren3d(p);
	mlx_hook(win->mlx_w, 2, 0, key_hook, p);
	mlx_loop(win->mlx_p);
}