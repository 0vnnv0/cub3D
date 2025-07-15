/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:10:56 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/11 18:44:38 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

void	draw_rect(t_raycast *data, t_ivec pxl, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			pix_put_img(data, pxl.x + j, pxl.y + i, color);
			j++;
		}
		i++;
	}
}

// alternative colors: 0x00008B (wall) and 0xADD8E6 (SPACE)
void	set_colors(t_raycast *data, char c, int x, int y)
{
	int		color;
	t_ivec	pxl;

	color = 0x000000;
	if (c == '1')
		color = 0xFF2E2E2E;
	else if (c == '0' || c == 'E' || c == 'W' || c == 'N' || c == 'S')
		color = 0xFFFFD1DC;
	else if (c == 'O')
		color = 0xffffff;
	else if (c == 'D')
		color = 0xBEBEBE;
	else
		color = 0;
	pxl.x = x * 10;
	pxl.y = y * 10;
	draw_rect(data, pxl, color);
}

void	draw_player(t_raycast *data, t_ivec pxl, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 7)
		{
			pix_put_img(data, pxl.x + j - 3, pxl.y + i -3, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_raycast *data)
{
	int		x;
	int		y;
	char	c;
	t_ivec	player;

	x = 0;
	y = 0;
	while (y < data->game->parser->height)
	{
		x = 0;
		while (x < data->game->parser->width)
		{
			c = data->game->parser->grid[y][x];
			set_colors(data, c, x, y);
			x++;
		}
		y++;
	}
	player.x = data->pos.x * 10;
	player.y = data->pos.y * 10;
	if (player.x >= 0 && player.y >= 0)
		draw_player(data, player, 0x8A2BE2);
}
//draw_rect(data, pxl, 0x8A2BE2);