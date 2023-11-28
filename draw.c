/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: aliburdi <aliburdi@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/23 14:35:59 by aliburdi		  #+#	#+#			 */
/*   Updated: 2023/11/25 15:15:06 by aliburdi		 ###   ########.fr	   */
/*																			*/
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

// void	draw_map2d(t_items *it)
// {
// 	int	x;
// 	int	y;
// 	int	start_x;
// 	int	start_y;
// 	int	end_x;
// 	int	end_y;

// 	for (y = 0; y < it->y_max; y++)
// 	{
// 		for (x = 0; x < it->x_max; x++)
// 		{
// 			if (it->matrix[y][x] == '1')
// 			{
// 				start_x = x * MAPS;
// 				start_y = y * MAPS;
// 				end_x = start_x + MAPS;
// 				end_y = start_y + MAPS;
// 				for (int i = start_x; i < end_x; i++)
// 				{
// 					for (int j = start_y; j < end_y; j++)
// 						my_mlx_pixel_put(it, i, j, 0xFFFFFF);
// 				}
// 			}
// 		}
// 	}
// 	mlx_put_image_to_window(it->mlx, it->win, it->img, 0, 0);
// }

void	draw_player_2d(t_items *it)
{
	int	i;
	int	j;

	j = -5;
	while (j < 5)
	{
		i = -5;
		while (i < 5)
		{
			my_mlx_pixel_put(it, it->px + i, it->py + j, 0xFFFF00);
			i++;
		}
		j++;
	}
	my_mlx_pixel_put(it, it->px, it->py, 0xFFFF00);
	draw_line(it->mlx, it->win, it->px, it->py, it->px + \
		it->pdx * 30, it->py + it->pdy * 30, 0xFFFF00);
}
