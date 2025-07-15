/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:06:55 by anschmit          #+#    #+#             */
/*   Updated: 2025/06/30 17:03:05 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
