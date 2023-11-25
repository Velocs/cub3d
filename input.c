/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:30:07 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/25 19:32:44 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	button_down(int key, t_items *it)
{
	if (key == 'w')
		it->w = 1;
	if (key == 'a')
		it->a = 1;
	if (key == 's')
		it->s = 1;
	if (key == 'd')
		it->d = 1;
	if (key == 65307)
		it->esc = 1;
	return (0);
}

int	button_up(int key, t_items *it)
{
	if (key == 'w')
		it->w = 0;
	if (key == 'a')
		it->a = 0;
	if (key == 's')
		it->s = 0;
	if (key == 'd')
		it->d = 0;
	if (key == 65307)
		it->esc = 0;
	return (0);
}

int movement(t_items *it)
{
	it->x0 = 0;
	it->y0 = 0;
	if (it->pdx < 0)
		it->x0 = -20;
	else
		it->x0 = 20;
	if (it->pdy < 0)
		it->y0 = -20;
	else
		it->y0 = 20;
	it->ipx = it->px / 64.0;
	it->ipx_add_x0 = (it->px + it->x0) / 64.0;
	it->ipx_sub_x0 = (it->px - it->x0) / 64.0;
	it->ipy = it->py / 64.0;
	it->ipy_add_y0 = (it->py + it->y0) / 64.0;
	it->ipy_sub_y0 = (it->py - it->y0) / 64.0;
	if (it->w == 1)
	{
		if (it->matrix[it->ipy][it->ipx_add_x0] == '0')
			it->px += it->pdx * 0.8;
		if (it->matrix[it->ipy_add_y0][it->ipx] == '0')
			it->py += it->pdy * 0.8;
	}
	if (it->a == 1)
	{
		it->pa += 1;
		it->pa = FixAng(it->pa);
		it->pdx = cos(degToRad(it->pa));
		it->pdy = -sin(degToRad(it->pa));
	}
	if (it->s == 1)
	{
		if (it->matrix[it->ipy][it->ipx_sub_x0] == '0')
			it->px -= it->pdx * 0.8;
		if (it->matrix[it->ipy_sub_y0][it->ipx] == '0')
			it->py -= it->pdy * 0.8;
	}
	if (it->d == 1)
	{
		it->pa -= 1;
		it->pa = FixAng(it->pa);
		it->pdx = cos(degToRad(it->pa));
		it->pdy = -sin(degToRad(it->pa));
	}
	if (it->esc == 1)
		ft_exit(it);
	ft_clear(it);
	drawceiling(it);
	drawfloor(it);
	draw_rays_2d(it);
	return (0);
}
