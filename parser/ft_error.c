/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:08:32 by rarahhal          #+#    #+#             */
/*   Updated: 2023/02/22 16:54:43 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_error(char *error)
{
	write(2, "Error\n", 6);
	(void)error;
	write(2, error, ft_strlen(error));
	exit(EXIT_FAILURE);
}