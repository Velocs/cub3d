/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:37:17 by lbusi             #+#    #+#             */
/*   Updated: 2023/12/03 19:19:58 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays_2d(t_items	*it)
{
	it->ra = fix_ang(it->pa + 30);
	it->r = 0;
	while (it->r < 120)
	{
		it->hmt = 0;
		it->vmt = 0;
		it->dof = 0;
		it->disv = 1000000;
		it->tang = tan(deg_to_rad(it->ra));
		boh(it);
		boh2(it);
		it->vx = it->rx;
		it->vy = it->ry;
		boh3(it);
		boh4(it);
		boh5(it);
		draw_3d_wall(it, it->r, it->lineoff, it->lineh);
		it->ra = fix_ang(it->ra - 0.5);
		it->r++;
	}
	mlx_put_image_to_window(it->mlx, it->win, it->img, 0, 0);
}
