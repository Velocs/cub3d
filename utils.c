/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:22:31 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/23 18:04:44 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;
	size_t	c;

	c = 0;
	i = ft_strlen(s1) - 4;
	while ((s2[c] == s1[i]) && (s1[i] != '\0'))
	{
		c++;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[c]);
}

void	initializer(t_items *it)
{
	it->mlx = mlx_init();
	it->win = mlx_new_window(it->mlx, 960, 640, "cub3d");
	it->img = mlx_new_image(it->mlx, 960, 640);
	it->addr = mlx_get_data_addr(it->img, &it->bits_per_pixel, &it->line_length, &it->endian);
	it->px = 150;
	it->py = 400;
	it->pa = 90;
	it->pdx = cos(degToRad(it->pa));
	it->pdy = -sin(degToRad(it->pa));
	it->thickness = 8;
	it->ipx = 0;
	it->ipx_add_x0 = 0;
	it->ipx_sub_x0 = 0;
	it->ipy = 0;
	it->ipy_add_y0 = 0;
	it->ipy_sub_y0 = 0;
	it->x0 = 0;
	it->y0 = 0;
}

int	ft_exit(t_items *it)
{
	mlx_destroy_window(it->mlx, it->win);
	free_matrix(it);
	exit (0);
	return (0);
}

void	ft_clear(t_items *it)
{
	mlx_destroy_image(it->mlx, it->img);
	it->img = mlx_new_image(it->mlx, 960, 640);
	it->addr = mlx_get_data_addr(it->img, &it->bits_per_pixel, &it->line_length, &it->endian);
}

void	my_mlx_pixel_put(t_items *it, int x, int y, int color)
{
	char	*dst;

	dst = it->addr + (y * it->line_length + x * (it->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
