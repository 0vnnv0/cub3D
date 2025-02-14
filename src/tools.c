/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:42:32 by mcheragh          #+#    #+#             */
/*   Updated: 2025/02/10 12:38:56 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	two_dim_len(char **arr)
{
	int	count;

	if (!arr)
		return (0);
	count = 0;
	while (arr[count])
		count++;
	return (count);
}

/**
 * select_texture - Determines which texture to use for a wall
 * @ray: Pointer to the ray structure
 *
 * This function selects the appropriate texture based on the direction
 * the ray was traveling when it hit a wall.
 * Returns: The texture index (NORTH, SOUTH, EAST, or WEST).
 */
int select_texture(t_ray *ray)
{
	if (ray->side == 0)  // Vertical walls
	{
		if (ray->dirx > 0)
			return EAST;
		else
			return WEST;
	}
	else  // Horizontal walls
	{
		if (ray->diry > 0)
			return SOUTH;
		else
			return NORTH;
	}
}
