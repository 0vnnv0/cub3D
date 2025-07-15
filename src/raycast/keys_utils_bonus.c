/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:11:46 by lea               #+#    #+#             */
/*   Updated: 2025/07/15 12:52:50 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

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
//alternative sound:
//if (system("aplay wall_leise.wav > /dev/null 2>&1 &") != 0)
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
	{
		if (data->game->map[y][x] == 'D')
			return (false);
		return (true);
	}
	if (system("aplay sound/wall_leise.wav > /dev/null 2>&1 &") != 0)
		return (false);
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
}
//start_raycast(data);

void	track_mouse(t_raycast *data)
{
	t_ivec	cursor;
	int		delta;
	double	angle;

	mlx_mouse_get_pos(data->game->mlx, data->game->win, &cursor.x, &cursor.y);
	delta = cursor.x - data->game->key.cursor;
	data->game->key.cursor = cursor.x;
	angle = delta * 0.5 * data->frame.frametime;
	rotate(data, angle);
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
	track_mouse(data);
	return (0);
}
