/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:00:37 by lbusi             #+#    #+#             */
/*   Updated: 2023/12/03 19:24:19 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_matrix(t_items *it)
{
	int	i;

	i = 0;
	while (i < it->y_max)
	{
		free(it->matrix[i]);
		i++;
	}
}

int	line_counter(t_items *it)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(it->map, O_RDONLY);
	if (fd < 1)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

int	column_counter(t_items *it)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	tmp = 0;
	while (it->matrix[i])
	{
		j = 0;
		while (it->matrix[i][j])
		{
			j++;
			if (tmp < j)
			{
				tmp = j;
			}
		}
		i++;
	}
	return (tmp);
}
