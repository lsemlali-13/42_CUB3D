/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:42:00 by lsemlali          #+#    #+#             */
/*   Updated: 2023/02/21 14:26:15 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

int	get_color(t_img data, int x, int y)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}

void	my_pixel_put(t_img data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	*(unsigned int *) dst = color;
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
