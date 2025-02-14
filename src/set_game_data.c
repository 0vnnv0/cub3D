#include "cub3D.h"

/*
 * Initializes an MLX texture from a given file path.
 * This function loads the texture into an MLX image and retrieves
 * its memory address for pixel manipulation.
 * 
 * Parameters:
 * - game: Pointer to the main game structure.
 * - index: Index of the texture in the texture array.
 * - path: Path to the texture file.
 */
void init_mlx_texture(t_game *game, int index, char *path)
{
    if (!path)
        print_error("Texture path is NULL\n");

    game->textures[index].img = mlx_xpm_file_to_image(
        game->mlx, path,
        &(game->textures[index].width),
        &(game->textures[index].height)
    );

    if (!game->textures[index].img)
    {
        print_error("Texture file could not be loaded: ");
        print_error(path); // prints the texture path that failed
		free_game(game);
    }

    game->textures[index].addr = mlx_get_data_addr(
        game->textures[index].img,
        &game->textures[index].bpp,
        &game->textures[index].line_len,
        &game->textures[index].endian
    );
	if (!game->textures[index].addr)
    {
        print_error("texture %d add is null", index);
		free_game(game);
    }
}

/*
 * Sets the player's initial direction and camera plane based on the given direction.
 * The camera plane determines the field of view for raycasting.
 * 
 * Parameters:
 * - game: Pointer to the main game structure.
 */
void set_dir(t_game *game)
{
    if (game->player.ini_dir == 'N') // Facing North
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0;
    }
    else if (game->player.ini_dir == 'S') // Facing South
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (game->player.ini_dir == 'W') // Facing West
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
    else if (game->player.ini_dir == 'E') // Facing East
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
}

/*
 * Loads the player's direction based on an initial direction string.
 * This function assigns the correct direction vector and camera plane.
 * 
 * Parameters:
 * - game: Pointer to the main game structure.
 */
void load_player(t_game *game)
{
    if (ft_strncmp(game->player.ini_dir, "N", 1) == 0)
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0;
    }
    else if (ft_strncmp(game->player.ini_dir, "S", 1) == 0)
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (ft_strncmp(game->player.ini_dir, "E",1) == 0)
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
    else if (ft_strncmp(game->player.ini_dir, "W",1) == 0)
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
	else{
		print_error("player direction not macthed\n");
		free_game(game);
	}
}