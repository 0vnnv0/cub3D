#include "cub3D.h"

/**
 * Initializes the floor and ceiling colors.
 * @param color Pointer to the color array for floor and ceiling.
 */
static void init_colors(t_color *color)
{
    // Initialize floor color properties
    color[FLOOR].color_str = NULL;
    color[FLOOR].texture = NULL;
    color[FLOOR].mode = 0;
    color[FLOOR].r = 0;
    color[FLOOR].g = 0;
    color[FLOOR].b = 0;

    // Initialize ceiling color properties
    color[CEILING].color_str = NULL;
    color[CEILING].texture = NULL;
    color[CEILING].mode = 0;
    color[CEILING].r = 0;
    color[CEILING].g = 0;
    color[CEILING].b = 0;
}

/**
 * Initializes the texture properties for each wall direction.
 * @param textures Pointer to the texture array.
 */
static void init_texture(t_texture *textures)
{
    // Initializing texture properties such as address, image, and dimensions
    textures[NORTH].addr = NULL;
    textures[SOUTH].addr = NULL;
    textures[WEST].addr = NULL;
    textures[EAST].addr = NULL;

    textures[NORTH].img = NULL;
    textures[SOUTH].img = NULL;
    textures[WEST].img = NULL;
    textures[EAST].img = NULL;

    textures[NORTH].path = NULL;
    textures[SOUTH].path = NULL;
    textures[WEST].path = NULL;
    textures[EAST].path = NULL;

    // Default dimensions for textures
    textures[NORTH].height = 32;
    textures[NORTH].width = 32;
    textures[SOUTH].height = 32;
    textures[SOUTH].width = 32;
    textures[WEST].height = 32;
    textures[WEST].width = 32;
    textures[EAST].height = 32;
    textures[EAST].width = 32;
}

/**
 * Initializes player attributes such as position, direction, and camera plane.
 * @param player Pointer to the player structure.
 */
static void init_player(t_player *player)
{
    player->x = 0;       // Player's X position on the map
    player->y = 0;       // Player's Y position on the map
    player->dir_x = 0;   // X direction of the player
    player->dir_y = 0;   // Y direction of the player
    player->plane_x = 0; // Camera plane X for FOV calculations
    player->plane_y = 0; // Camera plane Y for FOV calculations
    player->ini_dir = NULL; // Initial direction (N, S, E, W)
}

/**
 * Initializes raycasting variables.
 * @param ray Pointer to the ray structure.
 */
static void init_ray(t_ray *ray)
{
    ray->dirx = 0;        // Ray direction X
    ray->diry = 0;        // Ray direction Y
    ray->mapx = 0;        // Current grid cell X
    ray->mapy = 0;        // Current grid cell Y
    ray->side_distx = 0;  // Distance to next X-side
    ray->side_disty = 0;  // Distance to next Y-side
    ray->deltadistx = 0;  // Distance from one X-side to next
    ray->deltadisty = 0;  // Distance from one Y-side to next
    ray->walldist = 0;    // Distance to the wall hit
    ray->stepx = 0;       // Step direction in X
    ray->stepy = 0;       // Step direction in Y
    ray->side = 0;        // Which side of the wall was hit
    ray->lineheight = 0;  // Height of the line to draw
    ray->drawstart = 0;   // Start point of drawing on screen
    ray->drawend = 0;     // End point of drawing on screen
}

/**
 * Initializes the game structure, setting up default values.
 * @param game Pointer to the game structure.
 */
void init_game(t_game *game)
{
    game->mlx = NULL;        // MiniLibX instance
    game->win = NULL;        // Window instance
    game->height = SCREEN_HEIGHT; // Game screen height
    game->width = SCREEN_WIDTH;   // Game screen width
    game->map = NULL;        // Pointer to the game map

    init_player(&game->player);   // Initialize player properties
    init_texture(game->textures); // Initialize textures
    init_colors(game->color);     // Initialize floor and ceiling colors
    init_ray(&game->ray);         // Initialize raycasting variables
}

/**
 * Initializes raycasting properties for a specific screen column.
 * @param ray Pointer to the ray structure.
 * @param game Pointer to the game structure.
 * @param x Current column being processed.
 * 
 * camera_x: Maps screen X-coordinates into a normalized range [-1,1].
	dirx, diry: Set the direction of the ray using player FOV.
	mapx, mapy: Track which grid cell the ray is in.
	deltadistx, deltadisty: Step sizes for ray traversal.
 */
void init_mlx_ray(t_ray *ray, t_game *game, int x)
{
    // Calculate camera plane offset based on screen position
    double camera_x = 2 * x / (double)game->width - 1;

    // Calculate initial ray direction
    ray->dirx = game->player.dir_x + game->player.x * camera_x;
    ray->diry = game->player.dir_y + game->player.y * camera_x;

    // Set initial ray position in the map grid
    ray->mapx = (int)game->player.x;
    ray->mapy = (int)game->player.y;

    // Avoid division by zero when calculating delta distances
    ray->deltadistx = (ray->dirx == 0) ? 1e30 : fabs(1 / ray->dirx);
    ray->deltadisty = (ray->diry == 0) ? 1e30 : fabs(1 / ray->diry);
	calculate_step(ray, game);

}
