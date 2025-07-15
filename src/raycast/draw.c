/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:57:47 by lea               #+#    #+#             */
/*   Updated: 2025/07/13 21:27:09 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pix_put_img(t_raycast *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->buffer.addr
		+ (y * data->buffer.line_len + x * (data->buffer.bpp / 8));
	*(int *)pixel = color;
}

void	render_background(t_raycast *data)
{
	int	x;
	int	y;
	int	color;

	color = rgb_to_int(data->game->parser->ceiling);
	y = 0;
	while (y < data->game->screen.h)
	{
		x = 0;
		while (x < data->game->screen.w)
			pix_put_img(data, x++, y, color);
		y++;
		if (y == data->game->screen.h / 2)
			color = rgb_to_int(data->game->parser->floor);
	}
}

void	get_texture(t_raycast *data)
{
	if (data->side == 1)
	{
		if ((double)data->square.y < data->pos.y)
			data->tex.num = NO;
		else
			data->tex.num = SO;
	}
	else
	{
		if ((double)data->square.x < data->pos.x)
			data->tex.num = WE;
		else
			data->tex.num = EA;
	}
	data->tex.size.w = data->game->parser->textures[data->tex.num].width;
	data->tex.size.h = data->game->parser->textures[data->tex.num].height;
}

void	get_wallsize(t_raycast *data)
{
	data->lheight = (int)(data->game->screen.h / data->perpwalldist);
	data->start = -data->lheight / 2 + data->game->screen.h / 2;
	if (data->start < 0)
		data->start = 0;
	data->end = data->lheight / 2 + data->game->screen.h / 2;
	if (data->end >= data->game->screen.h)
		data->end = data->game->screen.h -1;
}

void	render_line(t_raycast *data, int x)
{
	int			color;
	t_texture	tex;
	int			y;

	get_wallsize(data);
	get_texture(data);
	get_tex_x(data);
	tex = data->game->parser->textures[data->tex.num];
	y = data->start;
	while (y < data->end)
	{
		data->tex.tex.y = (int)data->tex.pos % data->tex.size.h;
		data->tex.pos += data->tex.step;
		data->tex.bytes = tex.bits_per_pixel / 8;
		data->tex.pxl = tex.addr + data->tex.tex.y * tex.line_length
			+ data->tex.tex.x * data->tex.bytes;
		color = 0;
		ft_memcpy(&color, data->tex.pxl, data->tex.bytes);
		pix_put_img(data, x, y, color);
		y++;
	}
	return ;
}

/* void	draw_line(t_raycast *data, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		mlx_pixel_put(data->game->mlx, data->game->win, x, y, color);
		y++;
	}
	return ;
} */

/* void	put_line(t_raycast *data, int x)
{
	int	height;
	int	start;
	int	end;
	int	color;

	//calculate height of line and start and end point in pxl
	height = (int)(data->game->screen.h / data->perpwalldist);
	start = -height / 2 + data->game->screen.h / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + data->game->screen.h / 2;
	if (end >= data->game->screen.h)
		end = data->game->screen.h -1;
	// set_color funtion later for NESW
	if (data->side == 1)
		color = 0xFFFFFF;
	else
		color = 0xEEEEEE; //0xDDDDDD
	draw_line(data, x, start, end, color);
	return ;
} */
