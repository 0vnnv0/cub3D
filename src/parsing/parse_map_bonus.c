/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:06:55 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/09 18:26:31 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

int	check_map_name(char *mapname)
{
	int	len;

	if (!mapname)
		return (printf(RED "Error: No map name provided\n" RESET), 1);
	len = ft_strlen(mapname);
	if (len < 5)
		return (printf(RED "Error: Map name too short to be valid\n" RESET), 1);
	if (mapname[len - 4] != '.' || mapname[len - 3] != 'c'
		|| mapname[len - 2] != 'u' || mapname[len - 1] != 'b')
		return (printf(RED "Error: Wrong map format\n" RESET), 1);
	return (0);
}

void	handle_map_line(t_map *map, char *line)
{
	int		i;
	char	**new_grid;

	i = 0;
	while (map->grid && map->grid[i])
		i++;
	new_grid = malloc((i + 2) * sizeof(char *));
	if (!new_grid)
		return ;
	i = 0;
	while (map->grid && map->grid[i])
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[i] = strdup(line);
	new_grid[i + 1] = NULL;
	free(map->grid);
	map->grid = new_grid;
	map->height = i + 1;
}

void	check_width(t_map *map, char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && ft_isspace(line[len - 1]))
	{
		len--;
	}
	line[len] = '\0';
	if (len > map->width)
		map->width = len;
}

char	*allocate_padded_line(char *src, int len, int width)
{
	char	*dst;
	int		i;

	dst = malloc(sizeof(char) * (width + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	normalize_map_width(t_map *map)
{
	int		i;
	int		len;
	char	*padded;

	i = 0;
	while (map->grid && map->grid[i])
	{
		len = ft_strlen(map->grid[i]);
		if (len - 1 <= map->width)
		{
			padded = allocate_padded_line(map->grid[i], len, map->width);
			if (!padded)
				return ;
			free(map->grid[i]);
			map->grid[i] = padded;
		}
		i++;
	}
}
