/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:48:18 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/28 15:59:01 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	boh(t_items *it)
{
	if (cos(deg_to_rad(it->ra)) > 0.001)
	{
		it->rx = (((int)it->px / 64) * 64) + 64;
		it->ry = (it->px - it->rx) * it->tang + it->py;
		it->xo = 64;
		it->yo = -it->xo * it->tang;
	}
	else if (cos(deg_to_rad(it->ra)) < -0.001)
	{
		it->rx = (((int)it->px / 64) * 64) - 0.0001;
		it->ry = (it->px - it->rx) * it->tang + it->py;
		it->xo = -64;
		it->yo = -it->xo * it->tang;
	}
	else
	{
		it->rx = it->px;
		it->ry = it->py;
		it->dof = 10;
	}
}

void	boh2(t_items *it)
{
	while (it->dof < 10)
	{
		it->mx = (int)(it->rx) / 64;
		it->my = (int)(it->ry) / 64;
		it->mp = it->my * it->x_max + it->mx;
		if (it->mp > 0 && it->mp < it->x_max * it->y_max && \
			it->matrix[it->mp / it->x_max][it->mp % it->x_max] == '1')
		{
			it->dof = 10;
			it->disv = cos(deg_to_rad(it->ra)) * (it->rx - it->px) - \
				sin(deg_to_rad(it->ra)) * (it->ry - it->py);
		}
		else
		{
			it->rx += it->xo;
			it->ry += it->yo;
			it->dof += 1;
		}
	}
}

void	boh3(t_items *it)
{
	it->dof = 0;
	it->dish = 1000000;
	it->hx = it->px;
	it->hy = it->py;
	it->tang = 1.0 / it->tang;
	if (sin(deg_to_rad(it->ra)) > 0.001)
	{
		it->ry = (((int)it->py / 64) * 64) - 0.0001;
		it->rx = (it->py - it->ry) * it->tang + it->px;
		it->yo = -64;
		it->xo = -it->yo * it->tang;
	}
	else if (sin(deg_to_rad(it->ra)) < -0.001)
	{
		it->ry = (((int)it->py / 64) * 64) + 64;
		it->rx = (it->py - it->ry) * it->tang + it->px;
		it->yo = 64;
		it->xo = -it->yo * it->tang;
	}
	else
	{
		it->ry = it->py;
		it->rx = it->px;
		it->dof = 8;
	}
}

void	boh4(t_items *it)
{
	while (it->dof < 10)
	{
		it->mx = (int)(it->rx) / 64;
		it->my = (int)(it->ry) / 64;
		it->mp = it->my * it->y_max + it->mx;
		if (it->mp > 0 && it->mp < it->x_max * it->y_max && \
			it->matrix[it->mp / it->x_max][it->mp % it->x_max] == '1')
		{
			it->dof = 10;
			it->hx = it->rx;
			it->hy = it->ry;
			it->dish = cos(deg_to_rad(it->ra)) * (it->rx - it->px) - \
			sin(deg_to_rad(it->ra)) * (it->ry - it->py);
		}
		else
		{
			it->rx += it->xo;
			it->ry += it->yo;
			it->dof += 1;
		}
	}
}

void	boh5(t_items *it)
{
	it->shade = 1;
	if (it->disv < it->dish)
	{
		it->shade = 0.5;
		it->rx = it->vx;
		it->ry = it->vy;
		it->dist = it->disv;
	}
	if (it->dish < it->disv)
	{
		it->rx = it->hx;
		it->ry = it->hy;
		it->dist = it->dish;
	}
	it->ca = it->pa - it->ra;
	if (it->ca < 0)
		it->ca += 2 * PI;
	if (it->ca > 2 * PI)
		it->ca -= 2 * PI;
	it->dist = it->dist * cos(deg_to_rad(it->ca));
	it->lineh = (MAPS * 640) / (it->dist);
	it->ty_step = 32.0 / (float)it->lineh;
	it->ty_off = 0;
	if (it->lineh > 640)
	{
		it->ty_off = (it->lineh - 640) / 2.0;
		it->lineh = 640;
	}
	it->lineoff = 320 - it->lineh / 2.0;
	it->ty = it->ty_off * it->ty_step;
	if(it->shade == 1)
	{
		it->hmt = 0;
		it->tx = (int)(it->rx / 2.0) % 32;
		if (it->ra > 180)
		{
			it->tx = 32 - it->tx;
			it->hmt = 1;	
		}
	}
	else
	{
		it->tx = (int)(it->ry / 2.0) % 32;
		it->hmt = 3;
		if (it->ra > 90 && it->ra < 270)
		{
			it->hmt = 2;
			it->tx = 32 - it->tx;
		}	
	}
}
