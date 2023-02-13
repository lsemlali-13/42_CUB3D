#include "cub3d.h"

double	degtorad(double ang)
{
	while (ang < 0)
		ang += 360.0;
	while (ang >= 360)
		ang -= 360.0;
	return (ang * M_PI / 180);
}

char	**read_map(int fd)
{
	char	s[1000];

	read(fd, s, 1000);
	return (ft_split(s, '\n'));
}

// void	my_pixel_put(t_img *data, int x, int y, int color)
// {
// 	char 
// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// t_point	get_sign(double ang)
// {
// 	t_point point;

// 	point.x = 0;
// 	point.y = 0;
// 	point.signx = 1;
// 	point.signy = 1;
// 	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
// 	{
// 		point.x = 50;
// 		point.signy = -1;
// 	}
// 	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
// 	{
// 		point.x = -50;
// 		point.signx = -1;
// 		point.signy = -1;
// 	}
// 	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
// 	{
// 		point.x = -50;
// 		point.signx = -1;
// 	}
// 	else
// 	{
// 		point.x = 50;
// 		// point.signx = -1;
// 	}
// 	return (point);
// }

t_point	get_hsign(double ang)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	point.signx = 1;
	point.signy = 1;
	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
	{
		point.x = 50;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
	{
		// point.x = -50;
		point.signx = -1;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
	{
		// point.x = -50;z
		point.signx = -1;
	}
	else
	{
		point.x = 50;
		// point.signx = -1;
	}
	return (point);
}

t_point	get_dirh(double ang)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	// if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
	// 	point.y = -1;
	if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
		point.x = -1;
	if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
		point.x = -1;
	return (point);
}

t_point	get_dirv(double ang)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
		point.y = -1;
	if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
		point.y = -1;
	return (point);
}

t_point	get_vsign(double ang)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	point.signx = 1;
	point.signy = 1;
	if (degtorad(ang) >= 0 && degtorad(ang) < M_PI / 2)
	{
		// point.y = -50;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI / 2 && degtorad(ang) < M_PI)
	{
		// point.y = -50;
		point.signx = -1;
		point.signy = -1;
	}
	else if (degtorad(ang) >= M_PI && degtorad(ang) < 3 * (M_PI / 2))
	{
		point.signx = -1;
		point.y = 50;
	}
	else
	{
		point.y = 50;
	}
	return (point);
}

int	is_wallh(t_player *p, int x, int y)
{
	t_point inc;

	inc = get_dirh(p->rayangle);
	x += inc.x;
	y += inc.y;
	int check = x < WIDTH / 50 && y < HEIGHT / 50 && x >= 0 && y >= 0;
	if (!check)
		return (-1);
	if (check && p->map[y][x] == '1')
		return (1);
	return (0);
}

int	is_wallv(t_player *p, int x, int y)
{
	t_point inc;

	inc = get_dirv(p->rayangle);
	x += inc.x;
	y += inc.y;
	int check = x < WIDTH / 50 && y < HEIGHT / 50 && x >= 0 && y >= 0;
	if (!check)
		return (-1);
	if (check && p->map[y][x] == '1')
		return (1);
	return (0);
}

// void	ddah(t_player *p)
// {
// 	double	hy = floor(p->y / 50) * 50.0;
// 	double	hx = p->x;
// 	double	sx = 50 / tan(degtorad(p->rayangle));
// 	double	sy = 50;

// 	if (hy != p->y)
// 		hx = p->x + ((hy - p->y) / tan(degtorad(p->rayangle)));
// 	if (get_dir(p->rayangle) == DOWNR || get_dir(p->rayangle) == DOWNL)
// 		hy += 50;
// 	if (get_dir(p->rayangle) == UPR || get_dir(p->rayangle) == UPL)
// 		sy *= -1;
// 	if ((get_dir(p->rayangle) == DOWNL || get_dir(p->rayangle) == UPL) && sx > 0)
// 		sx *= -1;
// 	if ((get_dir(p->rayangle) == DOWNR || get_dir(p->rayangle) == UPR) && sx < 0)
// 		sx *= -1;
// 	p->turnx = hx;
// 	p->turny = hy;

// 	if (get_dir(p->rayangle) == UPR || get_dir(p->rayangle) == UPL)
// 		(p->turny)--;
	
// 	while (p->turnx < WIDTH && p->turny < HEIGHT && p->turnx >= 0 && p->turny >= 0)
// 	{
// 		if (is_wall(p, p->turnx / 50, p->turny / 50))
// 			break ;
// 		p->turnx += sx;
// 		p->turny += sy;
// 	}
// }


void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	if(x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_line(double x1, double y1, double tox, double toy, int color, t_player *p)
{
	double dx = tox - x1;
	double dy = toy - y1;
	int pxs = sqrt((dx * dx) + (dy * dy));
	dx /= pxs;
	dy /= pxs;
	double px = x1;
	double py = y1;
	while (pxs)
	{
        mlx_pixel_put(p->win->mlx_p, p->win->mlx_w, px, py, color);
		px += dx;
		py += dy;
		--pxs;
	}
	return (0);
}

// void draw_line2(int x1, int y1, int x2, int y2, int color, t_player *p)
// {
//     double dx = abs(x2 - x1);
//     double dy = abs(y2 - y1);
//     double x = x1;
//     double y = y1;
//     double sx = x1 < x2 ? 1 : -1;
//     double sy = y1 < y2 ? 1 : -1;
//     double err = dx - dy;

//     while (x != x2 || y != y2) {
//         mlx_pixel_put(p->win->mlx_p, p->win->mlx_w, x, y, color);
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
//     mlx_pixel_put(p->win->mlx_p, p->win->mlx_w, x, y, color);
// }

void	ddah(t_player *p)
{
	// double dx = 50 / cos(degtorad(p->rayangle));
	double hx = 50, hy;
	t_point inc = get_hsign(p->rayangle);
	double x = floor(p->turnx / 50) * 50 + inc.x, y;
	hy = fabs(fabs(x - p->x) * tan(degtorad(p->rayangle)));
	y = p->turny + (hy * inc.signy);
	hy = fabs(50 * tan(degtorad(p->rayangle)));
	double tx, ty;
	// int clr[2] =  {ORANGE, GREEN};
	int i = 0;
	tx = p->x;
	ty = p->y;
	int k = 0;
	while (!is_wallh(p, x / 50, y / 50))
	{
		// draw_line(tx, ty, x, y, clr[i], p);
		tx = x;
		ty = y;
		x += hx * inc.signx;
		y += hy * inc.signy;
		p->turnx = x;
		p->turny = y;
		i = (i == 0 ? 1 : 0);
		k = -1;
	}
	if (is_wallh(p, x / 50, y / 50) == 1)
	{
		p->turnx = x;
		p->turny = y;
		// draw_line(tx, ty, x, y, clr[i], p);
	}
	if (is_wallv(p, x / 50, y / 50) == -1)
	{
		p->turnx = 10000;
		p->turny = 10000;
	}
}
void	ddav(t_player *p)
{
	// double dx = 50 / sin(degtorad(p->rayangle));
	double hx, hy = 50;
	t_point inc = get_vsign(p->rayangle);
	double y = floor(p->y / 50) * 50 + inc.y, x;
	hx = fabs(fabs(p->y - y) / tan(degtorad(p->rayangle)));
	x = p->x + (hx * inc.signx);
	hx = fabs(50 / tan(degtorad(p->rayangle)));
	double tx, ty;
	// int clr[2] =  {YELLOW, RED};
	int i = 0;
	tx = p->x;
	ty = p->y;
	int k = 0;
	while (!is_wallv(p, x / 50, y / 50))
	{
		// draw_line(tx, ty, x, y, clr[i], p);
		tx = x;
		ty = y;
		x += hx * inc.signx;
		y += hy * inc.signy;
		p->turnx = x;
		p->turny = y;
		i = (i == 0 ? 1 : 0);
		k = -1;
	}
	if (is_wallv(p, x / 50, y / 50) == 1)
	{
		p->turnx = x;
		p->turny = y;
		// draw_line(tx, ty, x, y, clr[i], p);
	}
	if (is_wallv(p, x / 50, y / 50) == -1)
	{
		p->turnx = 10000;
		p->turny = 10000;
	}
}
double	get_dis(double stx, double sty, double endx, double endy)
{
	return (sqrt(pow(endx - stx, 2) + pow(endy - sty, 2)));
}
void	dda(t_player *p)
{
	t_point hor;
	t_point ver;
	double dish, disv;
	ddah(p);
	hor.x = p->turnx;
	hor.y = p->turny;
	ddav(p);
	ver.x = p->turnx;
	ver.y = p->turny;
	dish = get_dis(p->x, p->y, hor.x, hor.y);
	disv = get_dis(p->x, p->y, ver.x, ver.y);
	// if (dish == 0)
	// 	dish = 10000;
	// if (disv == 0)
	// 	disv = 10000;
	p->turnx = dish > disv ? ver.x : hor.x;
	p->turny = dish > disv ? ver.y : hor.y;
	// draw_line(p->x, p->y, hor.x, hor.y, YELLOW, p);
	// draw_line(p->x, p->y, ver.x, ver.y, RED, p);
	// draw_line(p->x, p->y, p->turnx, p->turny, BLUE, p);
}

void	ren3d(t_player *p)
{
	p->rayangle = p->rotangle - (FOV / 2);
	// t_player tmp = *p;
	// t_img *p_img;
	// p_img = malloc(sizeof(t_img));
	// p_img->img = mlx_new_image(p->win->mlx_p, 1000, 500);
	// p_img->addr = mlx_get_data_addr(p_img->img, &(p_img->bits_per_pixel), &(p_img->line_length), &(p_img->endian));

	double rcos;
	double rsin;
	for (int i = 0; i < 1000; i++)
	{
		p->turnx = p->x;
		p->turny = p->y;
		rcos = cos(degtorad(p->rayangle)) / 20;
		rsin = sin(degtorad(p->rayangle)) / 20;
		// while (p->map[(int)p->turny / 50][(int)p->turnx / 50] != '1')
		// {
		// 	p->turnx += rcos;
		// 	p->turny += rsin;
		// }
		dda(p);
		draw_line(p->x, p->y, p->turnx, p->turny, BLUE, p);
		// ddah(p);
		// draw_line(p->x, p->y, p->turnx, p->turny, YELLOW, p);
		// double dis = sqrt(pow(p->x - p->turnx, 2) + pow(p->y - p->turny, 2));
		// double wallh = (50 / dis) * (250 / 2);
		// tmp.x = i;
		// tmp.y = 0;
		// draw_line(&tmp, i, 250 - wallh, BLUE);
		// tmp.y = 250 - wallh;
		// draw_line(&tmp, i, 250 + wallh, YELLOW);
		// tmp.y = 250 + wallh;
		// draw_line(&tmp, i, 500, RED);
		p->rayangle += FOV / 1000.0;
	}
	// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p_img->img, 0, 0);
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

void	clear_wind(t_player *p)
{
	int i = 0;
	int j;
	int x = 0;
	int y = 0;

	while (p->map[i])
	{
		j = 0;
		x = 0;
		while (p->map[i][j])
		{
			if (p->map[i][j] == '1')
				mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_1, x, y);
			else if (p->map[i][j] == 'p')
			{
				mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, x, y);
				// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, x, y);
			}
			else {
				mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, x, y);
			}
			j++;
			x += 50;
		}
		i++;
		y += 50;
	}
}

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
			if (map[i][j] == '1')
				mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_1, x, y);
			else if (map[i][j] == 'p')
			{
				p->x = x;
				p->y = y;
				p->x_idx = j;
				p->y_idx = i;
				p->rotangle = 0;
				p->turnx = x;
				p->turny = y;
				// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, x, y);
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
	double x = p->x + cos(degtorad(p->rotangle)) * SPEED;
	double y = p->y - sin(degtorad(p->rotangle)) * SPEED;
	if (key == UP && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		clear_wind(p);
		p->x += cos(degtorad(p->rotangle)) * SPEED;
		p->y -= sin(degtorad(p->rotangle)) * SPEED;
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	x = p->x - cos(degtorad(p->rotangle)) * SPEED;
	y = p->y + sin(degtorad(p->rotangle)) * SPEED;
	if (key == DOWN && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		clear_wind(p);
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x -= cos(degtorad(p->rotangle)) * SPEED;
		p->y += sin(degtorad(p->rotangle)) * SPEED;
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	x = p->x - cos(degtorad(90 + p->rotangle)) * SPEED;
	y = p->y + sin(degtorad(90 + p->rotangle)) * SPEED;
	if (key == RIGHT && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		printf("%f, %f --- %f, %f\n", p->x, p->y, x, y);
		clear_wind(p);
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		// p->rotangle += 90;
		p->x -= cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y += sin(degtorad(90 + p->rotangle)) * SPEED;
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	x = p->x + cos(degtorad(90 + p->rotangle)) * SPEED;
	y = p->y - sin(degtorad(90 + p->rotangle)) * SPEED;
	if (key == LEFT && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		clear_wind(p);
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x += cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y -= sin(degtorad(90 + p->rotangle)) * SPEED;
		// mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
		p->y_idx = p->y / 50;
		ren3d(p);
	}
	if (key == ROTR)
	{
		clear_wind(p);
		p->rotangle -= 5;
		ren3d(p);
	}
	if (key == ROTL)
	{
		clear_wind(p);
		p->rotangle += 5;
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

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	int *h = 50 / , *w = 5;
// 	t_img	img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

// 	img = mlx_xpm_file_to_image(mlx, "textures/player.xpm", w, h);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }

