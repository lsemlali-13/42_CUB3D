/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:02:19 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/14 12:03:37 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/get_next_line.h"

void	ft_check_extention(char *str)
{
	int	n;

	n = ft_strlen(str);
	if (str[n - 4] == '.' && str[n - 3] == 'c'
		&& str[n - 2] == 'u'
		&& str[n - 1] == 'b')
		return ;
	ft_error("CHECK_EXTENTION\n");
}

void	ft_check_file(t_game *game)
{
	char	*line;
	int		fd;

	ft_check_extention(game->file_name);
	fd = open(game->file_name, O_RDONLY);
	if (fd <= 0)
		ft_error("error in opening file\n");
	line = get_next_line_2(fd);
	if (!line)
		ft_error("Error in map (vide)\n");
	free(line);
	close(fd);
}
