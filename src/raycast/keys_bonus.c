/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:22 by lea               #+#    #+#             */
/*   Updated: 2025/07/11 17:33:42 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

void	set_hooks(t_raycast *data)
{
	mlx_hook(data->game->win, 2, 1L << 0, set_action, data);
	mlx_hook(data->game->win, 3, 1L << 1, unset_action, data);
	mlx_hook(data->game->win, 17, 0, exit_loop, data->game);
	mlx_mouse_move(data->game->mlx,
		data->game->win,
		data->game->screen.w / 2,
		data->game->screen.h / 2);
	data->game->key.cursor = data->game->screen.w / 2;
}
//mlx_mouse_hide(data->game->mlx, data->game->win);

void	toggle_door(t_raycast *data)
{
	t_ivec	check;

	check.x = data->pos.x + data->dir.x;
	check.y = data->pos.y + data->dir.y;
	if (!data->game->map[check.y][check.x])
		return ;
	if (data->game->map[check.y][check.x] == 'D')
	{
		data->game->map[check.y][check.x] = 'O';
		if (system("aplay sound/tuer.wav > /dev/null 2>&1 &") != 0)
			return ;
	}
	else if (data->game->map[check.y][check.x] == 'O')
	{
		data->game->map[check.y][check.x] = 'D';
		if (system("aplay sound/tuer.wav > /dev/null 2>&1 &") != 0)
			return ;
	}
}

//printf("pressed %d\n", key);
int	set_action(int key, t_raycast *data)
{
	if (key == ESC)
	{
		exit_loop(data->game);
		return (0);
	}
	if (key == KEY_W)
		data->game->key.w = 1;
	if (key == KEY_A)
		data->game->key.a = 1;
	if (key == KEY_S)
		data->game->key.s = 1;
	if (key == KEY_D)
		data->game->key.d = 1;
	if (key == KEY_LEFT)
		data->game->key.l_arrow = 1;
	if (key == KEY_RIGHT)
		data->game->key.r_arrow = 1;
	if (key == SPACE)
		toggle_door(data);
	return (0);
}

//printf("released %d\n", key);
int	unset_action(int key, t_raycast *data)
{
	if (key == KEY_W)
		data->game->key.w = 0;
	if (key == KEY_A)
		data->game->key.a = 0;
	if (key == KEY_S)
		data->game->key.s = 0;
	if (key == KEY_D)
		data->game->key.d = 0;
	if (key == KEY_LEFT)
		data->game->key.l_arrow = 0;
	if (key == KEY_RIGHT)
		data->game->key.r_arrow = 0;
	return (0);
}
