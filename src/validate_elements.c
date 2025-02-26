/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:19:59 by mcheragh          #+#    #+#             */
/*   Updated: 2025/02/12 17:06:53 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//calls function to validate colors for floor and ceileing color 
int	validate_colors(t_color *color)
{
	if (!color[FLOOR].color_str || !color[CEILING].color_str)
	{
		printf("Error: Missing floor or ceiling color (F, C)\n");
		return (0);
	}
	if (!is_valid_color_texture(&color[FLOOR]))
	{
		printf("Error: Invalid floor color\n");
		return (0);
	}
	if (!is_valid_color_texture(&color[CEILING]))
	{
		printf("Error: Invalid ceiling color\n");
		return (0);
	}
	return (1);
}


//calls function to validate each texture
static int	validate_textures(t_texture *textures)
{
	if (!textures[NORTH].path || !textures[SOUTH].path || \
		!textures[WEST].path || !textures[EAST].path)
	{
		printf("Error: Missing one or more textures (NO, SO, WE, EA)\n");
		return (0);
	}
	if (!is_valid_texture_path(textures[NORTH].path) || \
		!is_valid_texture_path(textures[SOUTH].path) \
		|| !is_valid_texture_path(textures[WEST].path) \
		|| !is_valid_texture_path(textures[EAST].path))
		return (0);
	return (1);
}

int	validate_map(t_game *game)
{
	cal_map_dim(&game);
	if (!game->map || \
	!is_map_closed_and_accessible(game, game->map, game->height, game->width))
	{
		printf("Error: Map is not properly enclosed ");
		printf("by walls or not accessible\n");
		return (0);
	}
	return (1);
}

//calls function to validate the data saved in the structs
int	validate_cub_elements(t_game *game)
{
	if (validate_textures(game->textures) &&
		validate_colors(game->color) && validate_map(game))
	{
		print_struct(game);
		return (1);
	}
	else
	{
		print_struct(game);
		return (0);
	}
}
