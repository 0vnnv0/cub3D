/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:50 by anschmit          #+#    #+#             */
/*   Updated: 2025/02/14 11:44:09 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * move_player - Moves the player in the game based on the key pressed.
 * @keycode: The key pressed (arrow keys for movement).
 * @game: Pointer to the game structure containing player and MLX info.
 */
// void move_player(int keycode, t_game *game)
// {
//     // Store the player's previous position
//     int old_x = game->player.x;
//     int old_y = game->player.y;

//     // Update player position based on key input
//     if (keycode == XK_Left)
//         game->player.x -= 5; // Move left
//     if (keycode == XK_Right)
//         game->player.x += 5; // Move right
//     if (keycode == XK_Up)
//         game->player.y -= 5; // Move up
//     if (keycode == XK_Down)
//         game->player.y += 5; // Move down

//     // Erase the previous player position by drawing a black pixel
//     mlx_pixel_put(game->mlx, game->win, old_x, old_y, 0x000000);

//     // Draw the player at the new position in pink
//     mlx_pixel_put(game->mlx, game->win, game->player.x, game->player.y, 0xFF69B4);

//     // Refresh the display to apply the changes
//     mlx_do_sync(game->mlx);
// }
