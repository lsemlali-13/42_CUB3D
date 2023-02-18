#include "cub3d.h"

char	**read_map(int fd)
{
	char	s[1000];

	read(fd, s, 1000);
	return (ft_split(s, '\n'));
}

unsigned int	get_color(t_img *data, int x, int y, t_player *p, double wallh)
{
	char *dst;

	// printf("%d --- %d\n", x,y);
	(void)p;
	(void)wallh;
	//x = (int)wallh % p->h;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	my_pixel_put(t_img *data, int x, int y, unsigned int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int draw_line(double x, double y, double toy, unsigned int color, t_img *p_img, t_player *p, double wallh, int k)
{
	(void)p;
	double py = y;
	int newy;
	// int newx;

	//newy = py - (floor(py / TILE_SIZE) * TILE_SIZE);
	//newx = x - (floor(x / TILE_SIZE) * TILE_SIZE);
	newy = 0;
	//int k = p->h / wallh;
	while (py < toy)
	{
		if (p->check == -1)
			color = get_color(&p->img, k, newy, p, wallh);
		my_pixel_put(p_img, x, py, (unsigned int )color);
		py++;
		newy += p->h / (2 * wallh);
		newy %= p->h;
		//if (newy > 2400)
		//{
		//	newx++;
		//	newy = 0;
		//}
	}
	return (0);
}

void	ren3d(t_player *p)
{
	p->rayangle = p->rotangle + (FOV / 2);

	t_img *p_img;
	p_img = malloc(sizeof(t_img));
	p_img->img = mlx_new_image(p->win->mlx_p, p->map_width, p->map_height);
	p_img->addr = mlx_get_data_addr(p_img->img, &(p_img->bits_per_pixel), &(p_img->line_length), &(p_img->endian));
	unsigned int color;
	int k = 0;
	for (int i = 0; i < p->map_width; i++)
	{
		p->tox = p->x;
		p->toy = p->y;
		dda(p, &color);
		if (i == 0)
			k = p->tox - floor(p->tox / TILE_SIZE) * TILE_SIZE;
		double dis = sqrt(pow(p->x - p->tox, 2.0) + pow(p->y - p->toy, 2.0));
		dis = dis * cos(degtorad(p->rayangle - p->rotangle));
		double wallh = roundf((p->map_height / dis) * TILE_SIZE);
		if (wallh > p->map_height / 2)
			wallh = p->map_height / 2;
		// draw_line(i, 0, (p->map_height / 2) - wallh, BLUE, p_img, p);
		if ((int)p->tox % TILE_SIZE == 0 && (int)(p->tox * 10) % 10  == 0)
			k = 0;
		
		printf("%d --- %f\n", k, wallh);
		draw_line(i, (p->map_height / 2) - wallh, (p->map_height / 2) + wallh, color, p_img, p, wallh, k);
		k += p->w / wallh;
		k %= p->w;
		// draw_line(i, (p->map_height / 2) + wallh,  p->map_height - 1, BLACK, p_img, p);
		p->rayangle -= FOV / p->map_width;
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
			x += TILE_SIZE;
		}
		i++;
		y += TILE_SIZE;
	}
}

void	get_player_pos(t_player *p, int c)
{
	if (c == 'E')
		p->rotangle = 0;
	if (c == 'N')
		p->rotangle = 90;
	if (c == 'W')
		p->rotangle = 180;
	if (c == 'S')
		p->rotangle = 270;
}

void	get_player_info(char **map, t_player *p)
{
	int i = 0;
	int j;

	p->map_width = 0;
	while (map[i])
	{
		j = 0;
		if (ft_strlen(map[i]) * TILE_SIZE > p->map_width)
			p->map_width = ft_strlen(map[i]) * TILE_SIZE;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S')
			{
				get_player_pos(p, map[i][j]);
				p->x = (j * TILE_SIZE) + TILE_SIZE / 2;
				p->y = (i * TILE_SIZE) + TILE_SIZE / 2;
				p->tox = p->x;
				p->toy = p->y;
			}
			j++;
		}
		i++;
	}
	p->map_height = i * TILE_SIZE;
}

int	is_valid(t_player *p, double x, double y)
{
	if (p->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map[(int)((y - 3) / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map[(int)((y + 3) / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map[(int)(y / TILE_SIZE)][(int)((x - 3) / TILE_SIZE)] == '1')
		return (0);
	if (p->map[(int)(y / TILE_SIZE)][(int)((x + 3) / TILE_SIZE)] == '1')
		return (0);
	return (1);
}

void	move_player(int key, t_player *p)
{
	double x = p->x + cos(degtorad(p->rotangle)) * SPEED;
	double y = p->y - sin(degtorad(p->rotangle)) * SPEED;
	if (key == UP && is_valid(p, x, y))
	{
		p->x += cos(degtorad(p->rotangle)) * SPEED;
		p->y -= sin(degtorad(p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x - cos(degtorad(p->rotangle)) * SPEED;
	y = p->y + sin(degtorad(p->rotangle)) * SPEED;
	if (key == DOWN && is_valid(p, x, y))
	{
		p->x -= cos(degtorad(p->rotangle)) * SPEED;
		p->y += sin(degtorad(p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x - cos(degtorad(90 + p->rotangle)) * SPEED;
	y = p->y + sin(degtorad(90 + p->rotangle)) * SPEED;
	if (key == RIGHT && is_valid(p, x, y))
	{
		p->x -= cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y += sin(degtorad(90 + p->rotangle)) * SPEED;
		ren3d(p);
	}
	x = p->x + cos(degtorad(90 + p->rotangle)) * SPEED;
	y = p->y - sin(degtorad(90 + p->rotangle)) * SPEED;
	if (key == LEFT && is_valid(p, x, y))
	{
		p->x += cos(degtorad(90 + p->rotangle)) * SPEED;
		p->y -= sin(degtorad(90 + p->rotangle)) * SPEED;
		ren3d(p);
	}
	if (key == ROTR)
	{
		p->rotangle -= 10;
		ren3d(p);
	}
	if (key == ROTL)
	{
		p->rotangle += 10;
		ren3d(p);
	}
}


int	key_hook(int keycode, void *p)
{
	t_player *pl = (t_player *)p;
	move_player(keycode, pl);
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
	win->height = TILE_SIZE;
	win->width = TILE_SIZE;
	win->mlx_p = mlx_init();
	p->win = win;
	fd = open("maps/map.cub", O_RDWR);
	map = read_map(fd);
	p->map = map;
	// int w = 100, h = 100;
	p->img.img = mlx_xpm_file_to_image(p->win->mlx_p, "img.xpm", &p->w, &p->h);
	p->img.addr = mlx_get_data_addr(p->img.img, &(p->img.bits_per_pixel), &(p->img.line_length), &(p->img.endian));

	get_player_info(map, p);
	printf("%d --- \n", p->map_width);
	win->mlx_w = mlx_new_window(win->mlx_p, p->map_width, p->map_height, "CUB3D");
	ren3d(p);
	mlx_hook(win->mlx_w, 2, 0, key_hook, p);
	mlx_loop(win->mlx_p);
}