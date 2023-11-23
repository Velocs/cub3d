/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:35:59 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/23 14:36:42 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_rays_2d(t_items	*it)
{
    int r, mx, my, mp, dof;
    float vx, vy, rx, ry, ra, xo, yo, disT;

    ra = FixAng(it->pa + 30);
    for (r = 0; r < 60; r++)
    {
        dof = 0;
		float disV = 1000000;
        float Tan = tan(degToRad(ra));
        if (cos(degToRad(ra)) > 0.001)
        {
            rx = (((int)it->px / 64) * 64) + 64;
            ry = (it->px - rx) * Tan + it->py;
            xo = 64;
            yo = -xo * Tan;
        }
        else if (cos(degToRad(ra)) < -0.001)
        {
            rx = (((int)it->px / 64) * 64) - 0.0001;
            ry = (it->px - rx) * Tan + it->py;
            xo = -64;
            yo = -xo * Tan;
        }
        else
        {
            rx = it->px;
            ry = it->py;
            dof = 10;
        }
        while (dof < 10)
        {
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            mp = my * it->x_max + mx;
            if (mp > 0 && mp < it->x_max * it->y_max && it->matrix[mp/it->x_max][mp%it->x_max] == '1')
			{
                dof = 10;
				disV = cos(degToRad(ra)) * (rx - it->px) -sin(degToRad(ra)) * (ry - it->py);
			}
			else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
		vx = rx;
		vy = ry;

		dof = 0;
		float disH = 1000000, hx = it->px, hy = it->py;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)it->py / 64) * 64) -0.0001;
            rx = (it->py - ry) * Tan + it->px;
            yo = -64;
            xo = -yo * Tan;
        }
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)it->py / 64) * 64) + 64;
            rx = (it->py - ry) * Tan + it->px;
            yo = 64;
            xo = -yo * Tan;
        }
        else
        {
            ry = it->py;
            rx = it->px;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            mp = my * it->y_max + mx;
            if (mp > 0 && mp < it->x_max * it->y_max && it->matrix[mp/it->x_max][mp%it->x_max] == '1')
			{
                dof = 8;
				hx = rx;
				hy = ry;
				disH = cos(degToRad(ra)) * (rx - it->px) - sin(degToRad(ra)) * (ry - it->py);
			}
			else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}

		float ca = it->pa-ra;
		if (ca < 0)
			 ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(degToRad(ca));
  		float lineH = (mapS * 320) / (disT);
		if (lineH > 320)
			lineH = 320;
  		float lineOff = 160 - lineH / 2;
		draw3DWall(it, r, lineOff, lineH);
		ra = FixAng(ra - 1);
    }
	mlx_put_image_to_window(it->mlx, it->win, it->img, 0, 0);
}

void drawMap2D(t_items *it)
{
	int x, y;
	for (y = 0; y < it->y_max; y++)
	{
		for (x = 0; x < it->x_max; x++)
		{
			if (it->matrix[y][x] == '1')
			{
				int startX = x * mapS;
				int startY = y * mapS;
				int endX = startX + mapS;
				int endY = startY + mapS;

				// Disegna un quadrato per il valore 1
				for (int i = startX; i < endX; i++)
				{
					for (int j = startY; j < endY; j++)
					{
						my_mlx_pixel_put(it, i, j, 0xFFFFFF);
					}
				}
			}
		}
	}
	mlx_put_image_to_window(it->mlx, it->win, it->img, 0, 0);

}

void drawPlayer2D(t_items *it)
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
	drawLine(it->mlx, it->win, it->px, it->py, it->px + it->pdx * 30, it->py + it->pdy * 30, 0xFFFF00);
}
