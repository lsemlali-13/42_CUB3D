#include "cub3d.h"

char	**read_map(int fd)
{
	char	s[1000];

	read(fd, s, 1000);
	return (ft_split(s, '\n'));
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
				mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, x, y);
				mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, x, y);
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

void	move_player(int key, t_player *p)
{
	if (key == UP && p->map[(p->y - 10) / 50][p->x_idx] != '1')
	{
		printf("---- %d\n", p->y);
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->y -= 10;
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->y_idx = p->y / 50;
	}
	if (key == DOWN && p->map[(p->y + 10) / 50][p->x_idx] != '1')
	{
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->y += 10;
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->y_idx = p->y / 50;
	}
	if (key == RIGHT && p->map[p->y_idx][(p->x + 10) / 50] != '1')
	{
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x += 10;
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
	}
	if (key == LEFT && p->map[p->y_idx][(p->x - 10) / 50] != '1')
	{
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_0, (p->x / 50) * 50, p->y - (p->y % 50));
		p->x -= 10;
		mlx_put_image_to_window(p->win->mlx_p, p->win->mlx_w, p->win->img_p, p->x, p->y);
		p->x_idx = p->x / 50;
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
	win->mlx_w = mlx_new_window(win->mlx_p, 1000, 500, "hello");
	win->img_0 = mlx_xpm_file_to_image(win->mlx_p, "textures/black.xpm", &win->height, &win->width);
	win->img_p = mlx_xpm_file_to_image(win->mlx_p, "textures/player.xpm", &p->height, &p->width);
	win->img_1 = mlx_xpm_file_to_image(win->mlx_p, "textures/gray.xpm", &win->height, &win->width);
	p->win = win;
	fd = open("maps/map.cub", O_RDWR);
	map = read_map(fd);
	p->map = map;
	create_wind(map, p);
	mlx_hook(win->mlx_w, 2, 0, key_hook, p);
	mlx_loop(win->mlx_p);
}