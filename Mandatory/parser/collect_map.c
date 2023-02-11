#include "../../includes/cub3d.h"

void    collect_map(t_game *game, int index)
{
    int i;

    i = 0;
    while(!game->map_contant[index][0])
		index++;
	game->map.height = 0;
    while(game->map_contant[index + game->map.height][0]
        && game->map.height + index < game->size - 1)
    {
        // printf("----------------------\n");
	    // printf("%s\n", game->map_contant[index + game->map.height]);
        // printf("++++++++++++++++++++++\n");
        // if (game->map.height + index < game->size - 1)
        //     break;
        game->map.height++;
        if (game->map_contant[index + game->map.height][0] != '1'
			&& game->map_contant[index + game->map.height][0] != ' ')
            	ft_error("error in map\n");
        // if(!game->map_contant[index][0])
		//     ft_error("error in map\n");

        // printf("index :%d\n", index);
        // printf("size :%d\n", game->size);
        // printf("height :%d\n", game->map.height);
    }
	game->map.map = malloc(sizeof(char*) * (game->map.height));
    while(game->map_contant[index] && index < game->size)
        game->map.map[i++] = ft_strdup(game->map_contant[index++]);
}