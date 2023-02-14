#include "cub3d.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_line(double x, double y, double tox, double toy, int color, t_img *p_img)
{
	double py = y;
	(void)tox;
	while (py < toy)
	{
		my_pixel_put(p_img, x, py, color);
		py += 1;
	}
	return (0);
}

void	ren3d(t_player *p)
{
	p->rayangle = p->rotangle - (FOV / 2);

	t_img *p_img;
	p_img = malloc(sizeof(t_img));
	p_img->img = mlx_new_image(p->win->mlx_p, WIDTH, HEIGHT);
	p_img->addr = mlx_get_data_addr(p_img->img, &(p_img->bits_per_pixel), &(p_img->line_length), &(p_img->endian));
	int color;
	for (int i = 0; i < WIDTH; i++)
	{
		p->turnx = p->x;
		p->turny = p->y;
		dda(p, &color);
		double dis = sqrt(pow(p->x - p->turnx, 2.0) + pow(p->y - p->turny, 2.0));
		dis = dis * cos(degtorad(p->rayangle - p->rotangle));
		double wallh = roundf((HEIGHT / dis) * 15);
		if (wallh > HEIGHT / 2)
			wallh = HEIGHT / 2;
		// if ((int)p->turnx % 50 == 0)
		// 	color = GREEN;
		// else
		// 	color = YELLOW;
		draw_line(i, 0, i, (HEIGHT / 2) - wallh, BLUE, p_img);
		draw_line(i, (HEIGHT / 2) - wallh, i, (HEIGHT / 2) + wallh, color, p_img);
		draw_line(i, (HEIGHT / 2) + wallh, i, HEIGHT - 1, BLACK, p_img);
		p->rayangle += FOV / WIDTH;
	}
	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p_img->img, 0, 0);
}

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
			if (map[i][j] == 'p')
			{
				p->x = x;
				p->y = y;
				p->rotangle = 0;
				p->turnx = x;
				p->turny = y;
			}
			j++;
			x += 50;
		}
		i++;
		y += 50;
	}
	p->map_width = ft_strlen(map[0]) * 50;
	p->map_height = i * 50;
}

void	move_player(int key, t_player *p)
{
	double x = p->x + cos(degtorad(p->rotangle)) * SPEED * 3;
	double y = p->y - sin(degtorad(p->rotangle)) * SPEED * 3;
	if (key == UP && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x += cos(degtorad(p->rotangle)) * SPEED;
		p->y -= sin(degtorad(p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x - cos(degtorad(p->rotangle)) * SPEED * 3;
	y = p->y + sin(degtorad(p->rotangle)) * SPEED * 3;
	if (key == DOWN && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x -= cos(degtorad(p->rotangle)) * SPEED;
		p->y += sin(degtorad(p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x + cos(degtorad(90 + p->rotangle)) * SPEED * 3;
	y = p->y - sin(degtorad(90 + p->rotangle)) * SPEED * 3;
	if (key == RIGHT && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x += cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y -= sin(degtorad(90 + p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x - cos(degtorad(90 + p->rotangle)) * SPEED * 3;
	y = p->y + sin(degtorad(90 + p->rotangle)) * SPEED * 3;
	if (key == LEFT && p->map[(int)y / 50][(int)x / 50] != '1')
	{
		p->x -= cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y += sin(degtorad(90 + p->rotangle)) * SPEED;
		ren3d(p);
	}
	if (key == ROTR)
	{
		p->rotangle += 10;
		ren3d(p);
	}
	if (key == ROTL)
	{
		p->rotangle -= 10;
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
	win = malloc(sizeof(t_win));
	win->height = 50;
	win->width = 50;
	win->mlx_p = mlx_init();
	win->mlx_w = mlx_new_window(win->mlx_p, WIDTH, HEIGHT, "CUB3D");
	
	p->win = win;
	fd = open("maps/map.cub", O_RDWR);
	map = read_map(fd);
	p->map = map;
	create_wind(map, p);
	ren3d(p);
	mlx_hook(win->mlx_w, 2, 0, key_hook, p);
	mlx_loop(win->mlx_p);
}