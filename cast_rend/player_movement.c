#include "../includes/raycasting.h"

int	is_valid(t_player *p, double x, double y)
{
	if (p->map->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map->map[(int)((y - 5) / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map->map[(int)((y + 5) / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		return (0);
	if (p->map->map[(int)(y / TILE_SIZE)][(int)((x - 5) / TILE_SIZE)] == '1')
		return (0);
	if (p->map->map[(int)(y / TILE_SIZE)][(int)((x + 5) / TILE_SIZE)] == '1')
		return (0);
	return (1);
}

void    move_and_rend(t_player *p, double ang)
{
    if (is_valid(p, p->x + cos(degtorad(ang)) * SPEED, p->y - sin(degtorad(ang)) * SPEED))
    {
        p->x += cos(degtorad(ang)) * SPEED;
        p->y -= sin(degtorad(ang)) * SPEED;
        ren3d(p);
    }
}

void	move_player(int key, t_player *p)
{
	if (key == UP)
        move_and_rend(p, p->rotangle);
	if (key == DOWN)
        move_and_rend(p, p->rotangle - 180);
	if (key == RIGHT)
        move_and_rend(p, p->rotangle - 90);
	if (key == LEFT)
        move_and_rend(p, p->rotangle + 90);
	if (key == ROTR)
	{
		p->rotangle -= 6;
		ren3d(p);
	}
	if (key == ROTL)
	{
		p->rotangle += 6;
		ren3d(p);
	}
}