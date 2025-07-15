/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:18:46 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/09 18:12:08 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_cell_enclosed(t_map *map, int y, int x)
{
	const char	*valid;

	valid = "01NSEW";
	if (y <= 0 || y >= map->height -1 || x <= 0 || x >= map->width)
		return (0);
	if (!ft_strchr(valid, map->grid[y - 1][x]))
		return (0);
	if (!ft_strchr(valid, map->grid[y + 1][x]))
		return (0);
	if (!ft_strchr(valid, map->grid[y][x - 1]))
		return (0);
	if (!ft_strchr(valid, map->grid[y][x + 1]))
		return (0);
	if (!ft_strchr(valid, map->grid[y - 1][x - 1]))
		return (0);
	if (!ft_strchr(valid, map->grid[y - 1][x + 1]))
		return (0);
	if (!ft_strchr(valid, map->grid[y + 1][x - 1]))
		return (0);
	if (!ft_strchr(valid, map->grid[y + 1][x + 1]))
		return (0);
	return (1);
}

int	check_neighbour(t_map *map, int y, int x, char player)
{
	const char	*valid;

	valid = "10";
	if (player == 'E' || player == 'W' || player == 'S' || player == 'N')
	{
		if (y <= 0 || y >= map->height -1 || x <= 0 || x >= map->width - 1)
			return (0);
		if (!ft_strchr(valid, map->grid[y - 1][x]))
			return (0);
		if (!ft_strchr(valid, map->grid[y + 1][x]))
			return (0);
		if (!ft_strchr(valid, map->grid[y][x - 1]))
			return (0);
		if (!ft_strchr(valid, map->grid[y][x + 1]))
			return (0);
		if (!ft_strchr(valid, map->grid[y - 1][x - 1]))
			return (0);
		if (!ft_strchr(valid, map->grid[y - 1][x + 1]))
			return (0);
		if (!ft_strchr(valid, map->grid[y + 1][x - 1]))
			return (0);
		if (!ft_strchr(valid, map->grid[y + 1][x + 1]))
			return (0);
	}
	return (1);
}

int	validate_map_enclosure(t_map *map)
{
	int		i;
	int		j;
	char	player;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr("0NSEW", map->grid[i][j]))
			{
				player = map->grid[i][j];
				if (!is_cell_enclosed(map, i, j))
					return (exit_with_error(map, NULL, "map is open"));
				if (!check_neighbour(map, i, j, player))
					return (exit_with_error(map, NULL, "map is open"));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map_chars(t_map *map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			c = map->grid[i][j];
			if (!ft_strchr("01NSEW \t", c))
				return (exit_with_error(map, NULL, "invalid char"));
			if (ft_strchr("NSEW", c))
				save_player(map, c, i, j);
			j++;
		}
		i++;
	}
	if (map->player_count != 1)
	{
		return (exit_with_error(map, NULL, "invalid nr of players"));
	}
	return (0);
}

int	validate_map(t_map *map)
{
	if (map->grid == NULL || map->height == 0 || map->width == 0)
		return (exit_with_error(map, NULL, "no map found"));
	if (validate_map_chars(map))
		return (1);
	if (validate_map_enclosure(map))
		return (1);
	return (0);
}
