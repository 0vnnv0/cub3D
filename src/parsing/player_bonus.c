/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:06:55 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/15 13:30:22 by lhagemos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

void	save_player(t_map *map, char position, int i, int j)
{
	if (map->player_count == 0)
	{
		map->player_dir = position;
		map->player_y = i;
		map->player_x = j;
	}
	map->player_count++;
}

int	check_map2(t_map *map, int i, int j)
{
	char	player;

	player = map->grid[i][j];
	if (map->grid[i][j] == 'D')
	{
		if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
			return (exit_with_error(map, NULL, "door at edge of map"));
	}
	if (!is_cell_enclosed(map, i, j))
		return (exit_with_error(map, NULL, "map is open"));
	if (!check_neighbour(map, i, j, player))
		return (exit_with_error(map, NULL, "map is open"));
	return (0);
}
