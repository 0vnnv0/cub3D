/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:23 by lhagemos          #+#    #+#             */
/*   Updated: 2025/07/11 16:07:05 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->config_count = 0;
	map->header_done = 0;
	map->map_started = 0;
	map->player_dir = 0;
	map->player_count = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->floor[0] = 0;
	map->floor[1] = 0;
	map->floor[2] = 0;
	map->ceiling[0] = 0;
	map->ceiling[1] = 0;
	map->ceiling[2] = 0;
	map->f_set = 0;
	map->c_set = 0;
}

void	init_textures(t_texture *textures)
{
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;

}*/

void	initialise_game(t_map *map)
{
	ft_memset(map, 0, sizeof(t_map));
}
