/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:29:10 by anschmit          #+#    #+#             */
/*   Updated: 2025/02/14 12:30:48 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
 * Handles closing the game window.
 * Destroys the MLX display and exits the program.
 * 
 * Parameters:
 * - game: Pointer to the main game structure.
 */
// int close_window(t_game *game)
// {
//     mlx_destroy_display(game->mlx);
//     exit(0);
// }

int close_window(t_game *game)
{
    // Destroy the game window if it exists
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);

    // Free textures if they exist
    for (int i = 0; i < 4; i++) 
    {
        if (game->textures[i].img)
            mlx_destroy_image(game->mlx, game->textures[i].img);
    }

    // Free map memory if allocated
    if (game->map)
    {
        for (int i = 0; game->map[i]; i++)
            free(game->map[i]); // Free each row of the map
        free(game->map); // Free the map itself
    }

    // Destroy the MLX instance
    mlx_destroy_display(game->mlx);
    free(game->mlx); // Free the MLX pointer

    exit(0);
}


/*
 * Creates and initializes the game window, textures, and rendering system.
 * Also sets up MLX hooks for user input and rendering.
 * 
 * Parameters:
 * - game: Pointer to the main game structure.
 */
void create_window(t_game *game)
{
    // Initialize player data
    load_player(game);

    // Initialize MLX
    game->mlx = mlx_init();
    if (game->mlx == NULL)
        print_error("Error! MLX initialization failed!");

    // Create the game window
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    if (game->win == NULL)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        print_error("Error! MLX window creation failed!");
    }

    // Initialize framebuffer for rendering
    game->img = mlx_new_image(game->mlx, SCREEN_HEIGHT, SCREEN_WIDTH);
    if (!game->img)
    {
        printf("Error: mlx_new_image() failed!\n");
        return;
    }
    game->addr = mlx_get_data_addr(game->img, &game->bpp,
        &game->line_len, &game->endian);

    // Initialize player positioning and direction
    game->player.x += 0.5;
    game->player.y += 0.5;
    game->last_mouse_x = SCREEN_WIDTH / 2;
    game->key = -1;
    game->map_size = game->width;
   // set_dir(game);

    // Load wall textures
    init_mlx_texture(game, NORTH, game->textures[NORTH].path);
    init_mlx_texture(game, SOUTH, game->textures[SOUTH].path);
    init_mlx_texture(game, WEST, game->textures[WEST].path);
    init_mlx_texture(game, EAST, game->textures[EAST].path);

    // Set up rendering and input handling
	mlx_hook(game->win, KeyPress, KeyPressMask, &press_key, game);
	mlx_hook(game->win, DestroyNotify, ButtonPressMask, &free_game, game);
    mlx_hook(game->win, 17, 0, &close_window, game);
    mlx_loop_hook(game->mlx, &render, game);
    mlx_loop(game->mlx);
	
}
