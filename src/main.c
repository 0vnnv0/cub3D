/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:18:29 by anschmit          #+#    #+#             */
/*   Updated: 2025/02/12 17:39:57 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


/*Proper Way: Using Images (mlx_put_image_to_window)
Instead of drawing each pixel one by one, it's better to:

Create an image buffer using mlx_new_image().
Modify pixel values directly in memory instead of calling mlx_pixel_put().
Display the final image with mlx_put_image_to_window().

Raycasting (t_ray) → Determines what to draw
Image Buffer (t_texture or mlx image) → Stores the pixels efficiently
Display (mlx_put_image_to_window) → Shows the final frame

in mlx_put_image_to_window(mlx, win, img, x, y), the x and y parameters specify where the 
image should be placed inside the window.
✅ For cub3D (Full-Screen Rendering)
Since we want to render the game view from the top-left corner (0,0) to fill 
the entire screen, we should use:

mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
x = 0 → Place the image at the leftmost part of the window.
y = 0 → Place the image at the top of the window.

*/
int	render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);  // ✅ Display final frame

	return 0;
}

int	main(int argc, char *argv[])
{
	t_game *game;

	if (argc != 2)
		return (printf("Error: Please provide a map file\n"), 1);
	// Dynamically allocate memory for the game structure
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		print_error("Error: Memory allocation failed\n");
		return (1);
	}
	init_game(game);
	if (!pars_file(argv[1], game, argv))
	{
		free_game(game);
		return (1);
	}
	printf("Map loaded successfully!\n");
	create_window(game);
	free_game(game);
	return (0);
}
