/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:07:58 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/30 16:46:22 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	readfile(t_items *it)
{
	int		fd;
	int		i;

	i = it->y_max;
	it->y = 0;
	fd = open(it->map, O_RDONLY);
	if (fd == -1)
		exit(0);
	it->file = (char *) calloc((i) + 1, sizeof(char *));
	it->matrix = (char **)calloc((80), sizeof(char **));
	if (!it->file)
		return ;
	while (i > 0)
	{
		it->file = get_next_line(fd);
		file_check(it);
		if (it->file[0] == '1' || it->file[0] == '0')
			it->y++;
		i--;
	}
	it->y_max = it->y;
	close(fd);
	it->file = NULL;
}

void	file_check(t_items *it)
{
	int	i;

	i = 0;
	while (it->file[i])
	{
		if (it->file[i] == 'N' && it->file[i + 1] == 'O' && it->no == 0)
		{
			it->no = check_line(it->file);
			break ;
		}
		else if (it->file[i] == 'S' && it->file[i + 1] == 'O' && it->so == 0)
		{
			it->so = check_line(it->file);
			break ;
		}
		else if (it->file[i] == 'E' && it->file[i + 1] == 'A' && it->ea == 0)
		{
			it->ea = check_line(it->file);
			break ;
		}
		else if (it->file[i] == 'W' && it->file[i + 1] == 'E' && it->we == 0)
		{
			it->we = check_line(it->file);
			break ;
		}
		else if (it->file[i] == 'F')
		{
			it->floor = check_line(it->file);
			break ;
		}
		else if (it->file[i] == 'C')
		{
			it->ceiling = check_line(it->file);
			break ;
		}
		else if (it->file[i] == '1' || it->file[i] == '0')
		{
			it->matrix[it->y] = ft_strdup(it->file);
			break ;
		}
		i++;
	}
}

char	*check_line(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * ft_strlen(str));
	if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
		i += 2;
	if (str[i] == 'F' || str[i] == 'C')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int create_rgb(int red, int green, int blue)
{
    int color;
	
    red = (red > 255) ? 255 : (red < 0) ? 0 : red;
    green = (green > 255) ? 255 : (green < 0) ? 0 : green;
    blue = (blue > 255) ? 255 : (blue < 0) ? 0 : blue;
	color = (red << 16) | (green << 8) | blue;

    return color;
}

// void	read_rgb(t_items *it)
// {
// 	// int	i;
// 	// int	j;
// 	// int	tmp;

// 	// j = 0;
// 	// i = 0;
// 	// tmp = ft_atoi(it->floor);
// 	// printf("%d\n", tmp);
// 	// while (it->floor[i] && it->floor[i] != ',')
// 	// {
		
// 	// }
// }
