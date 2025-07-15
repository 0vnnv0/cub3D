/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:48:29 by lea               #+#    #+#             */
/*   Updated: 2025/07/13 21:26:04 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_dir_plane(t_raycast *data, char dir)
{
	data->dir.x = 0;
	data->dir.y = 0;
	data->plane.x = 0;
	data->plane.y = 0;
	if (dir == 'N')
	{
		data->dir.y = -1;
		data->plane.x = 0.66;
	}
	else if (dir == 'E')
	{
		data->dir.x = 1;
		data->plane.y = 0.66;
	}
	else if (dir == 'S')
	{
		data->dir.y = 1;
		data->plane.x = -0.66;
	}
	else if (dir == 'W')
	{
		data->dir.x = -1;
		data->plane.y = -0.66;
	}
}

void	init_raycast(t_raycast *data)
{
	data->game->screen.w = WIN_WIDTH;
	data->game->screen.h = WIN_HEIGHT;
	data->pos.x = (double)data->game->pos.x + 0.5;
	data->pos.y = (double)data->game->pos.y + 0.5;
	init_dir_plane(data, data->game->dir);
	data->frame.time = get_time();
	data->frame.oldtime = data->frame.time;
	create_img_buffer(data);
}

void	print_data(t_raycast *data)
{
	printf("frametime: %f and movespeed: %f\n",
		data->frame.frametime, data->frame.movespeed);
	printf("screen width: %d and height: %d\n",
		data->game->screen.w, data->game->screen.h);
	printf("pos x: %f and y: %f\n", data->pos.x, data->pos.y);
	printf("square x: %d and y: %d\n", data->square.x, data->square.y);
	printf("dir x: %f and y: %f\n", data->dir.x, data->dir.y);
	printf("plane x: %f and y: %f\n", data->plane.x, data->plane.y);
	printf("camerax: %f \n", data->camerax);
	printf("raydir x: %f and y: %f\n", data->raydir.x, data->raydir.y);
	printf("deltadist x: %f and y: %f\n", data->deltadist.x, data->deltadist.y);
	printf("sidedist x: %f and y: %f\n", data->sidedist.x, data->sidedist.y);
	printf("step x: %d and y: %d\n", data->step.x, data->step.y);
	printf("hit: %d \n", data->hit);
	printf("side: %d \n", data->side);
}

void	set_speed(t_raycast *data)
{
	data->frame.oldtime = data->frame.time;
	data->frame.time = get_time();
	data->frame.frametime = (double)(data->frame.time - data->frame.oldtime)
		/ 1000.0;
	if (data->frame.frametime <= 0)
		return ;
	data->frame.movespeed = data->frame.frametime * 1;
	data->frame.rotspeed = data->frame.frametime * 1;
}

//mlx_clear_window still necessary? Works without
int	start_raycast(t_raycast *data)
{
	int	x;

	render_background(data);
	x = 0;
	while (x < data->game->screen.w)
	{
		data->hit = false;
		get_raydir(data, x);
		get_deltadist(data);
		get_sidedist_step(data);
		perform_dda(data);
		render_line(data, x);
		x++;
	}
	mlx_put_image_to_window(data->game->mlx,
		data->game->win, data->buffer.ptr, 0, 0);
	return (0);
}
