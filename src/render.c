#include "cub3D.h"

/**
 * get_texture_pixel - Retrieves the color of a pixel from the texture.
 * @texture: Pointer to the texture structure.
 * @x: X coordinate on the texture.
 * @y: Y coordinate on the texture.
 *
 * Returns: The color of the pixel at the specified coordinates in the texture.
 * The function get_texture_pixel() is designed to extract the pixel color from 
 * a texture based on the x and y coordinates, and a given texture ID (tex_id). 
 * It takes a texture array, x, and y values as input and returns the pixel color as an integer.
 */
int get_texture_pixel(t_texture *texture, int x, int y, int tex_id)
{
    // Check if the texture is properly loaded
    if (!texture[tex_id].addr)
    {
        printf("Error: texture[%d]->addr is NULL\n", tex_id);
        return -1; // Return an error code or handle the error appropriately
    }

    // Ensure x, y are within bounds
    if (x < 0 || x >= texture[tex_id].width || y < 0 || y >= texture[tex_id].height)
    {
        printf("Error: Invalid coordinates x=%d, y=%d for texture[%d] (width=%d, height=%d)\n",
                x, y, tex_id, texture->width, texture->height);
        return -1; // Return an error code or handle the error appropriately
    }

    // Calculate the address of the pixel
    char *dst = texture[tex_id].addr + (y * texture[tex_id].line_len + x * (texture[tex_id].bpp / 8));

    // Return the color of the pixel
    return *(int *)dst;
}

/**
 * my_mlx_pixel_put - Puts a pixel with a specified color at the given screen coordinates.
 * 
 * This function writes a pixel at the specified screen position `(x, y)` in the texture
 * buffer used for rendering the screen. The function performs boundary checks, ensures
 * the texture image buffer is correctly initialized, checks the line length, and then writes
 * the color to the calculated pixel location. If any error occurs, the function will print
 * an error message and exit without modifying the image.
 *
 * @game: Pointer to the game structure containing texture data.
 * @x: The x-coordinate of the pixel to be modified.
 * @y: The y-coordinate of the pixel to be modified.
 * @color: The color (in RGBA format) to write to the pixel.
 */
static void my_mlx_pixel_put(t_game *game, int x, int y, int color, int tex_id)
{

    // Boundary check: Ensure the pixel (x, y) is within screen limits
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    {
        printf("Error: Pixel (%d, %d) out of bounds!\n", x, y);
        return;
    }

    // Texture buffer check: Ensure the image buffer is initialized
    if (!game->img || !game->addr)
    {
        printf("Error: Image buffer is not initialized!\n");
        return;
    }

    // Line length check: Ensure the line length is sufficient to hold the row of pixels
    // if (game->line_len < SCREEN_WIDTH * 4)
    // {
    //     printf("Error: line_len (%d) too small!\n", game->textures->line_len);
    //     return;
    // }

    // Calculate the destination address for the pixel based on x, y coordinates
    char *dst = game->addr + (y * game->line_len + x * (game->bpp / 8));

    // Null pointer check: Ensure the calculated pixel address is valid
    if (!dst)
    {
        printf("Error: dst is NULL! Cannot write pixel.\n");
        return;
    }

    // Write the color to the pixel at the calculated address
    *(unsigned int *)dst = color;
}


/**
 * render_wall_slice - Draws a vertical slice of a wall with textures
 * @game: Pointer to the game structure
 * @ray: Pointer to the ray structure
 * @x: The current screen column being drawn
 * @tex_id: The texture index to use
 *
 * This function retrieves texture data and draws a vertical slice of a
 * wall on the screen based on raycasting calculations.
 */
static void render_wall_slice(t_game *game, t_ray *ray, int x, int tex_id)
{
    int y;
    int tex_x;
    int tex_y;
    int color;
    double tex_pos;
    double step;

    // Calculate the x-position on the texture
    double wall_x = (ray->side == 0) ? (game->player.y + ray->walldist * ray->diry)
                                     : (game->player.x + ray->walldist * ray->dirx);
    wall_x -= floor(wall_x); 

    // Use texture width instead of TILE_SIZE
    tex_x = (int)(wall_x * game->textures[tex_id].width);
    if ((ray->side == 0 && ray->dirx > 0) || (ray->side == 1 && ray->diry < 0))
        tex_x = game->textures[tex_id].width - tex_x - 1; 

    // Calculate game->textures[tex_id] step size for vertical scaling
    step = 1.0 * game->textures[tex_id].height / ray->lineheight;
    tex_pos = (ray->drawstart - SCREEN_HEIGHT / 2 + ray->lineheight / 2) * step;
	for (y = ray->drawstart; y < ray->drawend; y++)
	{
		if (y < 0 || y >= SCREEN_HEIGHT) // Extra safety check
			continue;

		tex_y = (int)tex_pos % game->textures[tex_id].height;
		tex_pos += step;

		color = get_texture_pixel(game->textures, tex_x, tex_y, tex_id);
		if (ray->side == 1) 
			color = (color >> 1) & 0x7F7F7F; 

		my_mlx_pixel_put(game, x, y, color, tex_id);
	}

}

/**
 * cast_rays - Main raycasting function to render the scene
 * @game: Pointer to the game structure
 *
 * This function loops through all screen columns, casting a ray per column,
 * computing intersections with walls, and rendering the correct wall slices.
 * 
 * Loop Through Each Vertical Screen Column → Each column represents a ray.
	Initialize Ray (t_ray) → Calculate its direction based on the player’s position.
	Use DDA Algorithm to Find Wall Hits → Step through the grid to detect where the ray collides with a wall.
	Compute Distance to Wall → Needed for scaling wall height.
	Draw the Wall Strip → Convert the 3D projection into vertical lines on the screen.

 */
void cast_rays(t_game *game)
{
    t_ray ray;
    int x = 0;

    while (x < game->width)
    {
        init_mlx_ray(&ray, game, x);
        perform_dda(&ray, game);
        calculate_wall_height(&ray, game);
        // Determine which texture to use and render the wall slice
        int tex_id = select_texture(&ray);
        render_wall_slice(game, &ray, x, tex_id);
        x++;
    }
}
