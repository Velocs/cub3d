/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:22:31 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/30 16:19:50 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data *load(t_items *it, char *s)
{
	t_data	*data;
	int		b;

	data = malloc(sizeof(t_data));
	b = 32;
	data->img = mlx_xpm_file_to_image(it->mlx, s, &b, &b);
	if (data->img == NULL)
	{
		free(data);
		return (NULL);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (data);
	
}

void	load_texture(t_items *it)
{
	it->textures->ea = load(it, it->ea);
	it->textures->no = load(it, it->no);
	it->textures->so = load(it, it->so);
	it->textures->we = load(it, it->we);

}

void	initializer(t_items *it)
{
	it->no = 0;
	it->so = 0;
	it->ea = 0;
	it->we = 0;
	it->mlx = mlx_init();
	it->win = mlx_new_window(it->mlx, 960, 640, "cub3d");
	it->img = mlx_new_image(it->mlx, 960, 640);
	it->addr = mlx_get_data_addr(it->img, &it->bits_per_pixel, &it->line_length, &it->endian);
	it->px = 150;
	it->py = 400;
	it->thickness = 8;
	it->ipx = 0;
	it->ipx_add_x0 = 0;
	it->ipx_sub_x0 = 0;
	it->ipy = 0;
	it->ipy_add_y0 = 0;
	it->ipy_sub_y0 = 0;
	it->x0 = 0;
	it->y0 = 0;
	it->textures = calloc(1, sizeof(t_textures *));
}

void	initializer2(t_items *it)
{
	it->pdx = cos(deg_to_rad(it->pa));
	it->pdy = -sin(deg_to_rad(it->pa));
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
	*(unsigned int *)dst = color;
}

void	floor_rgb(t_items *it)
{
	char **rgb;
	
	rgb = ft_split(it->floor, ',');

	it->red_f = ft_atoi(rgb[0]);
	it->green_f = ft_atoi(rgb[1]);
	it->blue_f = ft_atoi(rgb[2]);
}

void	ceiling_rgb(t_items *it)
{
	char **rgb;
	
	rgb = ft_split(it->ceiling, ',');

	it->red_c = ft_atoi(rgb[0]);
	it->green_c = ft_atoi(rgb[1]);
	it->blue_c = ft_atoi(rgb[2]);
}