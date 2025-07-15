/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:05:46 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/11 14:48:38 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

void	cleanup_colors(char **colors)
{
	int	i;

	i = 0;
	if (!colors)
		return ;
	while (colors[i])
	{
		free(colors[i]);
		i++;
	}
	free(colors);
}

int	exit_with_error(t_map *map, char *cleanup, const char *msg)
{
	if (msg)
		printf(RED "Error: %s\n" RESET, msg);
	if (cleanup)
		free(cleanup);
	free_map(map);
	get_next_line(-1);
	return (1);
}

void	free_img(t_map *map)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (map->textures[i].img)
		{
			mlx_destroy_image(map->mlx, map->textures[i].img);
			map->textures[i].img = NULL;
		}
		if (map->textures[i].path)
		{
			free(map->textures[i].path);
			map->textures[i].path = NULL;
		}
		i++;
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	free_img(map);
	if (map->grid)
	{
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}
