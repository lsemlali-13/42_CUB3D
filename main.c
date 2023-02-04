#include "cub3d.h"

double	degtorad(double deg)
{
	return (deg * M_PI / 180);
}

char	**read_map(int fd)
{
	char	s[1000];

	read(fd, s, 1000);
	return (ft_split(s, '\n'));
}

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	if(x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// int draw_line(t_player *p, double tox, double toy, int color, t_img *p_img)
// {
// 	double dx = tox - p->x;
// 	double dy = toy - p->y;
// 	int pxs = sqrt((dx * dx) + (dy * dy));
// 	dx /= pxs;
// 	dy /= pxs;
// 	double px = p->x;
// 	double py = p->y;
// 	while (pxs && py < 500)
// 	{
// 		my_pixel_put(p_img, px, py, color);
// 		px += dx;
// 		py += dy;
// 		--pxs;
// 	}
// 	return (0);
// }

void draw_line(int x1, int y1, int x2, int y2, int color, t_img *img) {
    double dx = abs(x2 - x1);
    double dy = abs(y2 - y1);
    double x = x1;
    double y = y1;
    double sx = x1 < x2 ? 1 : -1;
    double sy = y1 < y2 ? 1 : -1;
    double err = dx - dy;

    while (x != x2 || y != y2) {
        my_pixel_put(img, x, y, color);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
    my_pixel_put(img, x, y, color);
}

void dda(t_player *p)
{
	double	hy = floor(p->y / 50) * 50;
	double	hx = p->x + ((p->y - hy) / tan(p->rayangle));
	double	sx = 50 / tan(p->rayangle);
	double	sy = tan(p->rayangle) * sx;

	p->turnx = p->x;
	p->turny = p->y;
	hx = p->x;
	hy = p->y;
	while (p->map[(int)hy / 50][(int)hx / 50] != '1')
	{
		hx += sx;
		hy += 50;
	}
	while (p->map[(int)p->turny / 50][(int)p->turnx / 50] != '1')
	{
		p->turnx += 50;
		p->turny += sy;
	}
}

void	ren3d(t_player *p)
{
	p->rayangle = p->rotangle - (FOV / 2);

	t_player tmp = *p;
	t_img *p_img;
	p_img = malloc(sizeof(t_img));
	int color = YELLOW;
	p_img->img = mlx_new_image(p->win->mlx_p, 1000, 500);
	p_img->addr = mlx_get_data_addr(p_img->img, &(p_img->bits_per_pixel), &(p_img->line_length), &(p_img->endian));
	double rcos;
	double rsin;
	for (int i = 0; i < WIDTH; i++)
	{
		p->turnx = p->x;
		p->turny = p->y;
		rcos = cos(degtorad(p->rayangle)) / 20;
		rsin = sin(degtorad(p->rayangle)) / 20;
		while (p->map[(int)p->turny / 50][(int)p->turnx / 50] != '1')
		{
			p->turnx += rcos;
			p->turny += rsin;
		}
		double dis = sqrt(pow(p->x - p->turnx, 2.0) + pow(p->y - p->turny, 2.0));
		dis = dis * cos(degtorad(p->rayangle - p->rotangle));
		double wallh = round((250 / dis) * 50);
		if (wallh > HEIGHT / 2)
			wallh = 249.0;
		tmp.x = i;
		tmp.y = 0;
		draw_line(i, 0, i, 250 - wallh, BLUE, p_img);
		tmp.y = 250 - wallh;
		draw_line(i, 250 - wallh, i, 250 + wallh, color, p_img);
		tmp.y = 250 + wallh;
		draw_line(i, 250 + wallh, i, 499, RED, p_img);
		p->rayangle += FOV / 1000.0;
	}
	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p_img->img, 0, 0);
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
			// if (map[i][j] == '1')
			// 	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_1, x, y);
			if (map[i][j] == 'p')
			{
				p->x = x;
				p->y = y;
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
	double x = p->x + cos(degtorad(p->rotangle)) * SPEED;
	double y = p->y + sin(degtorad(p->rotangle)) * SPEED;
	if (key == UP && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x += cos(degtorad(p->rotangle)) * SPEED;
		p->y += sin(degtorad(p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x - cos(degtorad(p->rotangle)) * SPEED;
	y = p->y - sin(degtorad(p->rotangle)) * SPEED;
	if (key == DOWN && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x -= cos(degtorad(p->rotangle)) * SPEED;
		p->y -= sin(degtorad(p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x + cos(degtorad(90 + p->rotangle)) * SPEED;
	y = p->y + sin(degtorad(90 + p->rotangle)) * SPEED;
	if (key == RIGHT && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x += cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y += sin(degtorad(90 + p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x - cos(degtorad(90 + p->rotangle)) * SPEED;
	y = p->y - sin(degtorad(90 + p->rotangle)) * SPEED;
	if (key == LEFT && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x -= cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y -= sin(degtorad(90 + p->rotangle)) * SPEED;
		ren3d(p);
	}
	if (key == ROTR)
	{
		p->rotangle += 10;
		if (p->rotangle > 327)
			p->rotangle -= 360;
		ren3d(p);
	}
	if (key == ROTL)
	{
		p->rotangle -= 10;
		if (p->rotangle < 0)
			p->rotangle += 360;
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