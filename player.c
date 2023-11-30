/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:38:22 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/30 17:35:28 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_pos(t_items *it)
{
	int	i;
	int	j;

	i = 0;
	while(it->matrix[i])
	{
		j = 0;
		while (it->matrix[i][j])
		{
			if (it->matrix[i][j] == 'N')
			{
				it->px = (j * 64) + 32;
				it->py = (i * 64) + 32;
				it->pa = 90;
				break;
			}
			else if (it->matrix[i][j] == 'W')
			{
				it->px = (j * 64) + 32;
				it->py = (i * 64) + 32;
				it->pa = 180;
				break;
			}
			else if (it->matrix[i][j] == 'S')
			{
				it->px = (j * 64) + 32;
				it->py = (i * 64) + 32;
				it->pa = 270;
				break;
			}
			else if (it->matrix[i][j] == 'E')
			{
				it->px = (j * 64) + 32;
				it->py = (i * 64) + 32;
				it->pa = 0;
				break;
			}
			j++;
		}
		i++;
	}
}
