#include "cub3d.h"

char	**read_map(int fd)
{
	char	s[1000];

	read(fd, s, 1000);
	return (ft_split(s, '\n'));
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