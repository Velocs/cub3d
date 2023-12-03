/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:51:41 by aliburdi          #+#    #+#             */
/*   Updated: 2023/12/03 19:52:11 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_path_helper(t_items *it)
{
	int		fd;

	fd = open(it->ea, O_RDONLY);
	if (fd == -1)
	{
		printf("Texture path error\n");
		ft_exit(it);
	}
	close(fd);
	fd = open(it->we, O_RDONLY);
	if (fd == -1)
	{
		printf("Texture path error\n");
		ft_exit(it);
	}
	close(fd);
}

void	check_path(t_items *it)
{
	int		fd;

	fd = open(it->no, O_RDONLY);
	if (fd == -1)
	{
		printf("Texture path error\n");
		ft_exit(it);
	}
	close(fd);
	fd = open(it->so, O_RDONLY);
	if (fd == -1)
	{
		printf("Texture path error\n");
		ft_exit(it);
	}
	close(fd);
	check_path_helper(it);
}
