#include "../../includes/cub3d.h"

void    check_first_line(char *line)
{
        int     i;

        i = -1;
        while (++i < ft_strlen(line) && line[i])
                if (line[i] != '1' && line[i] != ' ')
                        ft_error("Map must be closed/surrounded by walls.\n");
}

void    collect_map(t_game *game, int index)
{
    int i;

    i = 0;
    while(!game->map_contant[index][0])
		index++;
    game->map.size = 0;
    while(game->map_contant[index + game->map.size][0] && game->map.size + index < game->height - 1)
    {
        game->map.size++;
        if (game->map_contant[index + game->map.size][0] != '1' && game->map_contant[index + game->map.size][0] != ' ')
            ft_error("error in map\n");
    }
    // printf("%d\n", game->map.size);
    game->map.map = malloc(sizeof(char*) * (game->map.size + 1));
    while(game->map_contant[index] && index < game->height)
        game->map.map[i++] = ft_strdup(game->map_contant[index++]);
}