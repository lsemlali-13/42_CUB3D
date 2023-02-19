#include "cub3d.h"

char	**read_map(int fd)
{
	char	s[1000];

	read(fd, s, 1000);
	return (ft_split(s, '\n'));
}

unsigned int	get_color(t_img *data, int x, int y)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_img	get_wich(t_player *p)
{
	if (p->which_tex == 'E')
		return (p->img_e);
	if (p->which_tex == 'N')
		return (p->img_n);
	if (p->which_tex == 'W')
		return (p->img_w);
	return (p->img_s);
}

int draw_texture(double x, double y, double toy, t_img *p_img, t_player *p, double wallh)
{
	double newy;
	int color;
	t_img	img;

	img = get_wich(p);
	newy = 0;
	double inc = img.h / (2 * wallh);
	p->tox = floor((int)(img.w * ((p->tox + p->toy) / TILE_SIZE)) % img.w);
	if ((2 * wallh) > p->map_height)
		newy = (int)((((2 * wallh) - p->map_height) / 2) * inc) % img.h;
	while (y < toy)
	{
		color = get_color(&img, p->tox, roundf(newy));
		my_pixel_put(p_img, x, y, color);
		y++;
		newy += inc;
		if (newy > img.h)
			newy = (int)newy % img.h;
	}
	return (0);
}

int draw_line(double x, double y, double toy, int color, t_img *p_img)
{	
	while (y < toy)
	{
		my_pixel_put(p_img, x, y, color);
		y++;
	}
	return (0);
}

void	ren3d(t_player *p)
{
	p->rayangle = p->rotangle + (FOV / 2);

	t_img *p_img;
	// t_point dst;
	p_img = malloc(sizeof(t_img));
	p_img->img = mlx_new_image(p->win->mlx_p, p->map_width, p->map_height);
	p_img->addr = mlx_get_data_addr(p_img->img, &(p_img->bits_per_pixel), &(p_img->line_length), &(p_img->endian));
	for (int i = 0; i < p->map_width; i++)
	{
		p->tox = p->x;
		p->toy = p->y;
		dda(p);
		double dis = sqrt(pow(p->x - p->tox, 2.0) + pow(p->y - p->toy, 2.0));
		dis = dis * cos(degtorad(p->rayangle - p->rotangle));
		double wallh = roundf((p->map_height / dis) * TILE_SIZE);
		if (wallh > p->map_height / 2)
			wallh = p->map_height / 2;
		draw_line(i, 0, (p->map_height / 2) - wallh, BLUE, p_img);
		draw_texture(i, (p->map_height / 2) - wallh, (p->map_height / 2) + wallh, p_img, p, roundf((p->map_height / dis) * TILE_SIZE));
		draw_line(i, (p->map_height / 2) + wallh,  p->map_height - 1, BLACK, p_img);
		p->rayangle -= FOV / p->map_width;
	}
	mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p_img->img, 0, 0);
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
	if (p->map[(int)((y - 5) / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map[(int)((y + 5) / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map[(int)(y / TILE_SIZE)][(int)((x - 5) / TILE_SIZE)] == '1')
		return (0);
	if (p->map[(int)(y / TILE_SIZE)][(int)((x + 5) / TILE_SIZE)] == '1')
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

void	load_textures(t_player *p)
{
	p->img_e.img = mlx_xpm_file_to_image(p->win->mlx_p, "textures/img.xpm", &p->img_e.w, &p->img_e.h);
	p->img_n.img = mlx_xpm_file_to_image(p->win->mlx_p, "textures/img1.xpm", &p->img_n.w, &p->img_n.h);
	p->img_w.img = mlx_xpm_file_to_image(p->win->mlx_p, "textures/img2.xpm", &p->img_w.w, &p->img_w.h);
	p->img_s.img = mlx_xpm_file_to_image(p->win->mlx_p, "textures/img3.xpm", &p->img_s.w, &p->img_s.h);

	p->img_e.addr = mlx_get_data_addr(p->img_e.img, &(p->img_e.bits_per_pixel), &(p->img_e.line_length), &(p->img_e.endian));
	p->img_n.addr = mlx_get_data_addr(p->img_n.img, &(p->img_n.bits_per_pixel), &(p->img_n.line_length), &(p->img_n.endian));
	p->img_w.addr = mlx_get_data_addr(p->img_w.img, &(p->img_w.bits_per_pixel), &(p->img_w.line_length), &(p->img_w.endian));
	p->img_s.addr = mlx_get_data_addr(p->img_s.img, &(p->img_s.bits_per_pixel), &(p->img_s.line_length), &(p->img_s.endian));
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
	load_textures(p);
	get_player_info(map, p);
	win->mlx_w = mlx_new_window(win->mlx_p, p->map_width, p->map_height, "CUB3D");
	ren3d(p);
	mlx_hook(win->mlx_w, 2, 0, key_hook, p);
	mlx_loop(win->mlx_p);
}