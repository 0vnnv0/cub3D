/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:17:07 by lhagemos          #+#    #+#             */
/*   Updated: 2025/07/11 14:19:29 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// calculate the direction of the current ray
// and set starting pt: every ray starts at the position of the player
void	get_raydir(t_raycast *data, int x)
{
	data->camerax = 2 * x / (double) data->game->screen.w -1;
	data->raydir.x = data->dir.x + data->plane.x * data->camerax;
	data->raydir.y = data->dir.y + data->plane.y * data->camerax;
	data->square.x = (int)data->pos.x;
	data->square.y = (int)data->pos.y;
}

// calculate deltaDistance and avoid division by 0
void	get_deltadist(t_raycast *data)
{
	if (data->raydir.x != 0)
		data->deltadist.x = fabs(1 / data->raydir.x);
	else
		data->deltadist.x = 1e30;
	if (data->raydir.y != 0)
		data->deltadist.y = fabs(1 / data->raydir.y);
	else
		data->deltadist.y = 1e30;
}

// calculate initial sideDistance and step direction
void	get_sidedist_step(t_raycast *data)
{
	if (data->raydir.x < 0)
	{
		data->step.x = -1;
		data->sidedist.x = (data->pos.x - data->square.x) * data->deltadist.x;
	}
	else
	{
		data->step.x = 1;
		data->sidedist.x = (data->square.x + 1.0 - data->pos.x)
			* data->deltadist.x;
	}
	if (data->raydir.y < 0)
	{
		data->step.y = -1;
		data->sidedist.y = (data->pos.y - data->square.y) * data->deltadist.y;
	}
	else
	{
		data->step.y = 1;
		data->sidedist.y = (data->square.y + 1.0 - data->pos.y)
			* data->deltadist.y;
	}
}

void	perform_dda(t_raycast *data)
{
	while (data->hit == false)
	{
		if (data->sidedist.x < data->sidedist.y)
		{
			data->sidedist.x += data->deltadist.x;
			data->square.x += data->step.x;
			data->side = 0;
		}
		else
		{
			data->sidedist.y += data->deltadist.y;
			data->square.y += data->step.y;
			data->side = 1;
		}
		if (!(data->game->map[data->square.y][data->square.x])
			|| data->game->map[data->square.y][data->square.x] == '1')
			data->hit = true;
	}
	if (data->side == 0)
		data->perpwalldist = (data->sidedist.x - data->deltadist.x);
	else
		data->perpwalldist = (data->sidedist.y - data->deltadist.y);
	return ;
}
