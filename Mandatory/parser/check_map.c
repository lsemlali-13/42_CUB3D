#include "../../includes/cub3d.h"

void	check_line(char *line)
{
    int	i;

	i = 0;
	//  && i < ft_strlen(line)
	while (line[i])
	{
    	if (line[i] != '1' && line[i] != ' ')
            ft_error("Map must be closed/surrounded by walls.\n");
		i++;
	}
}

void	check_characters(char	c)
{
    if (c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != '0')
        ft_error("Map must be contian (10SNEW ).\n");
}

void	check_is_closed(char **map, int size)
{
	int	i;
	int	j;

	i = 1;
	while(map[i] && i < size)
	{
		j = 0;
		while (map[i][j] && j < ft_strlen(map[i]))
		{
			if ( map[i][j] != '1' && map[i][j] != ' ')
			{
				check_characters(map[i][j]);
				if (map[i - 1][j] && map[i][j - 1] && map[i][j + 1] && map[i + 1][j])
				{
					if (map[i - 1][j] == ' ' || map[i][j - 1] == ' '
						|| map[i][j + 1] == ' ' || map[i + 1][j] == ' ')
						ft_error("Map must be closed/surrounded by walls.\n");
				}
				else
					ft_error("Map must be closed/surrounded by walls.\n");
			}
			j++;
		}
		i++;
	}
}

void    check_map(t_map *map)
{	
	check_line(map->map[0]);
	check_is_closed(map->map, map->height);
	check_line(map->map[map->height]);
}
