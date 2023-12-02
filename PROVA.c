/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PROVA.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:22:43 by aliburdi          #+#    #+#             */
/*   Updated: 2023/12/02 19:09:56 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// unsigned int	get_pixel(t_items *it, int x, int y)
// {
// 	char	*dest;

// 	if (x <= 0 || x >= 64 || y <= 0 || y >= 64)
// 		return (1);
// 	dest = it->addr + (y * it->line_length + x * (it->bits_per_pixel / 8));
// 	return (*(unsigned int *)dest);
// }

// static t_data *load(t_data *mlx, char *s)
// {
// 	t_data	*data;
// 	int		a;
// 	int		b;

// 	data = malloc(sizeof(t_data));
// 	a = 64;
// 	b = 64;
// 	data->img = mlx_png_file_to_image(mlx->mlx_ptr, s, &a, &b);
// 	if (data->img == NULL)
// 	{
// 		free(data);
// 		return (NULL);
// 	}
// 	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
// 			&data->line_length, &data->endian);
// 	return (data);

// }

// void	ft_create_level(t_data *mlx)
// {
// 	mlx->map->textures = malloc(sizeof(t_textures));
// 	mlx->map->textures->ea = load(mlx, "src/wall_ea.png");
// 	mlx->map->textures->no = load(mlx, "src/wall_no.png");
// 	mlx->map->textures->so = load(mlx, "src/wall_so.png");
// 	mlx->map->textures->we = load(mlx, "src/wall_we.png");
// 	mlx->map->color = 0x00FFFF;
// 	mlx->map->depth = (int *)malloc(sizeof(float) * 1200);
// 	ft_map_convert(mlx);
// 	ft_get_player_pos(mlx);
// 	mlx->map->pa = 90;
// 	mlx->map->pdx = cos(degtorad(mlx->map->pa));
// 	mlx->map->pdy = -sin(degtorad(mlx->map->pa));
// 	printf("player found at x: %f y: %f\n", mlx->map->px, mlx->map->py);
// 	mlx_loop_hook(mlx->mlx_ptr, ft_draw, mlx);

// }

void	draw_line(void *mlx, void *win, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
	int sx = x1 < x2 ? 1 : -1;
	int dy = -abs(y2 - y1);
	int sy = y1 < y2 ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		mlx_pixel_put(mlx, win, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

unsigned int	get_pixel(t_data *img, int x, int y)
{
	char	*dest;

	if (x <= 0 || x >= 32 || y <= 0 || y >= 32)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
}

void	draw_3d_wall(t_items *it, int r, float lineOff, float lineH)
{
	for (int y = lineOff; y < lineOff + lineH; y++)
	{
		for (int i = 0; i <= it->thickness; i++)
		{
			if (it->hmt == 0)
				my_mlx_pixel_put(it, r * 8 + i, y, get_pixel(it->textures->no, it->tx, it->ty));
			else if (it->hmt == 3)
				my_mlx_pixel_put(it, r * 8 + i, y, get_pixel(it->textures->ea, it->tx, it->ty));
			else if (it->hmt == 1)
				my_mlx_pixel_put(it, r * 8 + i, y, get_pixel(it->textures->so, it->tx, it->ty));
			else if (it->hmt == 2)
				my_mlx_pixel_put(it, r * 8 + i, y, get_pixel(it->textures->we, it->tx, it->ty));
		}
		it->ty += it->ty_step;
	}
}

void	draw_ceiling(t_items *it)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	color = create_rgb(it->red_c, it->green_c, it->blue_c);
	while (y < 320)
	{
		x = 0;
		while (x < 960)
		{
			my_mlx_pixel_put(it, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_items *it)
{
	int	y;
	int	x;
	int	color;

	color = create_rgb(it->red_f, it->green_f, it->blue_f);
	y = 280;
	while (y < 640)
	{
		x = 0;
		while (x < 960)
		{
			my_mlx_pixel_put(it, x, y, color);
			x++;
		}
		y++;
	}
}

void	printnewmatrix(char **new_matrix)
{
	int	i;
	int	j;

	i = 0;
	while (new_matrix[i])
	{
		j = 0;
		while (new_matrix[i][j])
		{
			printf("%c", new_matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}


// char	**xd(t_items	*it)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**new_matrix;

// 	if (it->x_max > it->y_max)
// 	{
// 		k = it->x_max - it->y_max;
// 		new_matrix = (char**)malloc(sizeof(char*) * it->x_max);
// 		if (!new_matrix)
// 			return (NULL);
// 		printf("%d\n", k);
// 		while (k > 0)
// 		{
// 			i = 0;
// 			while (i < it->x_max - 1 && it->matrix[i])
// 			{
// 				new_matrix[i] = (char *)malloc(sizeof(char) * it->x_max);
// 				j = 0;
// 				while (it->matrix[i][j])
// 				{
// 					new_matrix[i][j] = it->matrix[i][j];
// 					j++;
// 				}
// 				i++;
// 			}
// 			new_matrix[i] = "1";
// 			new_matrix[i + 1] = "\0";
// 			k--;
// 		}
// 		it->y_max = it->x_max;
// 		return (new_matrix);
// 	}
// 	else if (it->y_max > it->x_max)
// 	{
// 		k = it->y_max - it->x_max;
// 		new_matrix = (char**)malloc(sizeof(char*) * it->y_max);
// 		if (!new_matrix)
// 			return (NULL);
// 		printf("%d\n", k);
// 		while (k > 0)
// 		{
// 			i = 0;
// 			while (i < it->y_max - 1 && it->matrix[i])
// 			{
// 				new_matrix[i] = (char *)malloc(sizeof(char) * it->y_max);
// 				j = 0;
// 				while (it->matrix[i][j])
// 				{
// 					new_matrix[i][j] = it->matrix[i][j];
// 					j++;
// 				}
// 				i++;
// 			}
// 			new_matrix[i] = "1";
// 			new_matrix[i + 1] = "\0";
// 			k--;
// 		}
// 		it->x_max = it->y_max;
// 		return (new_matrix);
// 	}
// 	return (it->matrix);
// }

size_t	ft_longest(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

char **xd(t_items *it) {
    char **new_matrix;
    int i, j;
	int o;
    int x = ft_longest(it->x_max, it->y_max); // Supponendo che ft_longest restituisca la dimensione massima tra x_max e y_max

    // Allocazione della memoria per la nuova matrice
    new_matrix = calloc(x, sizeof(char **));
    if (!new_matrix) {
        // Gestione dell'errore di allocazione della memoria
        return NULL;
    }

    // Allocazione della memoria per ciascuna riga di new_matrix e riempimento con '1'
    for (i = 0; i < x; i++) {
        new_matrix[i] = calloc(x, sizeof(char *));
        if (!new_matrix[i]) {
            // Gestione dell'errore di allocazione della memoria
            // Deallocazione della memoria allocata finora
            for (int j = 0; j < i; j++) {
                free(new_matrix[j]);
            }
            free(new_matrix);
            return NULL;
        }
		j = 0;
        while (j < x)
		{
            new_matrix[i][j] = '7';
			j++;
		}
        new_matrix[i][j] = '\0';
    }

    // Copia degli elementi da it->matrix a new_matrix
    for (i = 0; i < it->y_max; i++) {
        for (j = 0, o = 0; it->matrix[i][j] && o < it->x_max; j++, o++) {
            if (i < x && j < x) {
				if (it->matrix[i][o] == ' ')
				{
					o++;
				}
                new_matrix[i][j] = it->matrix[i][o];
            }
        }
    }
	it->x_max = x;
	it->y_max = x;
    return new_matrix;
}

int	main(int ac, char **av)
{
	t_items	it;

	if (ac == 2 && check_input(av) == 1)
	{
		it.map = av[1];
		initializer(&it);
		it.y_max = line_counter(&it);
		readfile(&it);
		it.x_max = column_counter(&it);
		if (it.x_max != it.y_max)
			it.matrix = xd(&it);
		printmatrix(&it);
		if (!validate_map(it.matrix, it.y_max, it.x_max))
		{
			printf("MAPP ERROR\n");
			ft_exit(&it);
		}
			//printf("%s\n%s\n%s\n%s\n%s\n%s\n", it.no, it.so, it.ea, it.we, it.ceiling, it.floor);
		player_pos(&it);
		printf("y_max: %d\nx_max: %d\n px %f py %f\n", it.y_max, it.x_max, it.px, it.py);
		initializer2(&it);
		load_texture(&it);
		draw_rays_2d(&it);
		floor_rgb(&it);
		ceiling_rgb(&it);
		mlx_hook(it.win, 2, (1L << 0), button_down, &it);
		mlx_hook(it.win, 3, 1L << 1, button_up, &it);
		mlx_loop_hook(it.mlx, movement, &it);
		mlx_hook(it.win, 17, 1L << 16, ft_exit, &it);
		mlx_loop(it.mlx);
	}
	else
		printf("Map error!\n");
	return (0);
}
