/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:13:14 by anschmit          #+#    #+#             */
/*   Updated: 2025/02/12 18:49:09 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * calculate_step - Determines step direction and initial side distances
 * @ray: Pointer to the ray structure
 * @game: Pointer to the game structure containing player info
 *
 * This function calculates whether the ray moves in a positive or negative
 * direction along the X and Y axes, setting step values accordingly.
 * It also calculates the initial side distances to determine when a ray
 * crosses a grid line.
 */
void	calculate_step(t_ray *ray, t_game *game)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (game->player.x - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (ray->mapx + 1.0 - game->player.x) * ray->deltadistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (game->player.y - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (ray->mapy + 1.0 - game->player.y) * ray->deltadisty;
	}
}

/**
 * perform_dda - Executes the Digital Differential Analyzer (DDA) algorithm
 * @ray: Pointer to the ray structure
 * @game: Pointer to the game structure containing the map
 *
 * This function moves the ray step by step across the 2D grid until it
 * hits a wall ('1'). It determines whether the ray moves in the X or Y
 * direction based on which side distance is smaller.
 */
void	perform_dda(t_ray *ray, t_game *game)
{
	int	hit = 0;

	// Continue stepping until a wall is hit or the ray goes out of bounds
	while (hit == 0 && ray->mapx >= 0 && ray->mapx < game->width - 1 &&
		   ray->mapy >= 0 && ray->mapy < game->height)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0; // Vertical wall hit
		}
		else
		{
			ray->side_disty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1; // Horizontal wall hit
		}

		// Check if the new grid position contains a wall
		if (game->map[ray->mapy][ray->mapx] == '1') 
			hit = 1;
	}
}

/**
 * calculate_wall_height - Determines the height of the wall slice
 * @ray: Pointer to the ray structure
 * @game: Pointer to the game structure
 *
 * This function calculates the perpendicular distance from the player
 * to the wall hit, which is used to determine how tall the wall should
 * appear on screen.
 */
void	calculate_wall_height(t_ray *ray, t_game *game)
{
    if (ray->side == 0)
        ray->walldist = (ray->side_distx - ray->deltadistx);
    else
        ray->walldist = (ray->side_disty - ray->deltadisty);

    ray->lineheight = (int)(SCREEN_HEIGHT / ray->walldist);

    // 🛠 Clamp draw start and end to screen boundaries
    ray->drawstart = -ray->lineheight / 2 + SCREEN_HEIGHT / 2;
    if (ray->drawstart < 0)
        ray->drawstart = 0;  // Prevent negative y-values

    ray->drawend = ray->lineheight / 2 + SCREEN_HEIGHT / 2;
    if (ray->drawend >= SCREEN_HEIGHT)
        ray->drawend = SCREEN_HEIGHT - 1;  // Prevent out-of-bounds pixels
}
