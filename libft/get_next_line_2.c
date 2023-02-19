/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rizqy <rizqy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:52:14 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/11 20:02:06 by rizqy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*join_and_free_2(char *save, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(save, buffer);
	free(save);
	return (temp);
}

char	*move_to_rest_2(char *stock)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	rest = ft_calloc((ft_strlen(stock) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (stock[i])
		rest[j++] = stock[i++];
	free(stock);
	return (rest);
}

char	*get_line_2(char *stock)
{
	char	*line;
	int		i;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] && stock[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*read_file_2(int fd, char *save)
{
	char	*buffer;
	int		byt_read;

	if (!save)
		save = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byt_read = 1;
	while (byt_read > 0)
	{
		byt_read = read(fd, buffer, BUFFER_SIZE);
		if (byt_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byt_read] = 0;
		save = join_and_free_2(save, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (save);
}

char	*get_next_line_2(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stock = read_file_2(fd, stock);
	if (!stock)
		return (NULL);
	line = get_line_2(stock);
	stock = move_to_rest_2(stock);
	return (line);
}
