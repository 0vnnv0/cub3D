/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:20:14 by lea               #+#    #+#             */
/*   Updated: 2025/07/09 22:19:19 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

void	create_img_buffer(t_raycast *data)
{
	t_screen	screen;

	screen = data->game->screen;
	data->buffer.ptr = mlx_new_image(data->game->mlx, screen.w, screen.h);
	data->buffer.addr = mlx_get_data_addr(
			data->buffer.ptr,
			&data->buffer.bpp,
			&data->buffer.line_len,
			&data->buffer.endian);
}

int	rgb_to_int(int *c)
{
	int	r;
	int	g;
	int	b;

	r = c[0];
	g = c[1];
	b = c[2];
	return ((r << 16) | (g << 8) | b);
}

void	get_tex_x(t_raycast *data)
{
	if (data->side == 0)
		data->tex.wallx = data->pos.y + data->perpwalldist * data->raydir.y;
	else
		data->tex.wallx = data->pos.x + data->perpwalldist * data->raydir.x;
	data->tex.wallx -= floor((data->tex.wallx));
	data->tex.tex.x = (int)(data->tex.wallx * (double)data->tex.size.w);
	if ((data->side == 0 && data->raydir.x > 0)
		|| (data->side == 1 && data->raydir.y < 0))
		data->tex.tex.x = data->tex.size.w - data->tex.tex.x -1;
	data->tex.step = 1.0 * data->tex.size.h / data->lheight;
	data->tex.pos = (data->start - data->game->screen.h
			/ 2 + data->lheight / 2) * data->tex.step;
}

time_t	get_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) < 0)
	{
		printf("Error: gettimeofday failed\n");
		return (0);
	}
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}
