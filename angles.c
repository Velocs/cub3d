/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:22:23 by aliburdi          #+#    #+#             */
/*   Updated: 2023/11/23 14:23:18 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int FixAng(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return a;
}

float degToRad(int a)
{
	return a * M_PI / 180.0;
}

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );
}