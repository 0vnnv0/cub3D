
#include "cub3D.h"

int free_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->textures[NORTH].addr);
	mlx_destroy_image(game->mlx, game->textures[SOUTH].addr);
	mlx_destroy_image(game->mlx, game->textures[WEST].addr);
	mlx_destroy_image(game->mlx, game->textures[EAST].addr);

	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);

	free_two_dim(game->map);
	// free(game->map);
	if (game->textures[NORTH].addr)
		free(game->textures[NORTH].addr);
	if (game->textures[SOUTH].addr)
		free(game->textures[SOUTH].addr);
	if (game->textures[WEST].addr)
		free(game->textures[WEST].addr);
	if (game->textures[EAST].addr)
		free(game->textures[EAST].addr);
	if (game->color[CEILING].texture)
		;
	free(game->color[CEILING].texture);
	if (game->color[FLOOR].texture)
		;
	free(game->color[FLOOR].texture);
	if (game->color[FLOOR].color_str)
		free(game->color[FLOOR].color_str);
	if (game->color[CEILING].color_str)
		free(game->color[CEILING].color_str);
	free(game);
	exit(EXIT_FAILURE);
}
