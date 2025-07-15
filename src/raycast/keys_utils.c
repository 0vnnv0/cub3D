/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:11:49 by lea               #+#    #+#             */
/*   Updated: 2025/07/11 15:55:14 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**** Calculations for rotations of vectors ****/
/*	a = angle * PI / 180 (convert degree to radians for sin/cos ft
	double x_new = x * cos(angle) - y * sin(angle);
	double y_new = x * sin(angle) + y * cos(angle);
	if angle is pos nbr => rotation is clockwise 
	if angle is neg nbr => rotation is counterclockwise
	(in normal c-system its the otherway around but my c-system y goes down)
	When player rotates:
	both direction vector and plane vector have to be rotated
	Then, the rays will all automaticly rotate as well. */
void	rotate(t_raycast *data, double rot)
{
	double	x;
	double	y;

	x = data->dir.x;
	y = data->dir.y;
	data->dir.x = (x * cos(rot)) - (y * sin(rot));
	data->dir.y = (x * sin(rot)) + (y * cos(rot));
	x = data->plane.x;
	y = data->plane.y;
	data->plane.x = (x * cos(rot)) - (y * sin(rot));
	data->plane.y = (x * sin(rot)) + (y * cos(rot));
	start_raycast(data);
}

// opt indicates rather I check the destination of x or y
// and the direction of up/right or down/left
// 0 = x & '+'
// 1 = y & '+'
// 2 = x & '-'
// 3 = y & '-'
int	check_path(t_raycast *data, char opt, t_dvec dir)
{
	int	x;
	int	y;

	x = data->pos.x;
	y = data->pos.y;
	if (opt == 0)
		x = data->pos.x + dir.x * data->frame.movespeed;
	else if (opt == 1)
		y = data->pos.y + dir.y * data->frame.movespeed;
	else if (opt == 2)
		x = data->pos.x - dir.x * data->frame.movespeed;
	else if (opt == 3)
		y = data->pos.y - dir.y * data->frame.movespeed;
	if (data->game->map[y][x]
			&& data->game->map[y][x] != '1')
		return (true);
	else
		return (false);
}

void	move(t_raycast *data, t_move key, t_dvec dir)
{
	if (key == UP || key == RIGHT)
	{
		if (check_path(data, 0, dir) == true)
			data->pos.x = data->pos.x + dir.x * data->frame.movespeed;
		if (check_path(data, 1, dir) == true)
			data->pos.y = data->pos.y + dir.y * data->frame.movespeed;
	}
	else
	{
		if (check_path(data, 2, dir) == true)
			data->pos.x = data->pos.x - dir.x * data->frame.movespeed;
		if (check_path(data, 3, dir) == true)
			data->pos.y = data->pos.y - dir.y * data->frame.movespeed;
	}
	start_raycast(data);
}

int	apply_key(t_raycast *data)
{
	if (data->game->key.w == 1)
		move(data, UP, data->dir);
	if (data->game->key.s == 1)
		move(data, DOWN, data->dir);
	if (data->game->key.a == 1)
		move(data, LEFT, data->plane);
	if (data->game->key.d == 1)
		move(data, RIGHT, data->plane);
	if (data->game->key.l_arrow == 1)
		rotate(data, -data->frame.rotspeed);
	if (data->game->key.r_arrow == 1)
		rotate(data, data->frame.rotspeed);
	return (0);
}
