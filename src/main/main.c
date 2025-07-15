/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:56:02 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/15 13:42:49 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_keys(t_pro *game)
{
	game->key.w = 0;
	game->key.a = 0;
	game->key.s = 0;
	game->key.d = 0;
	game->key.l_arrow = 0;
	game->key.r_arrow = 0;
	game->key.esc = 0;
}

void	parse_data(t_raycast *data, t_pro *game, t_map *parser)
{
	init_keys(game);
	data->game = game;
	parser->mlx = data->game->mlx;
	load_all_textures(parser, game);
	data->game->parser = parser;
	data->game->dir = parser->player_dir;
	data->game->pos.x = parser->player_x;
	data->game->pos.y = parser->player_y;
	data->game->map = parser->grid;
}

int	engine(t_raycast *data)
{
	set_speed(data);
	apply_key(data);
	start_raycast(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_pro		game;
	t_map		new_map;
	char		*filename;
	int			check;
	t_raycast	*data;

	check = 1;
	filename = argv[1];
	if (argc != 2)
		return (printf(RED "Error: Wrong number of arguments!\n" RESET), 1);
	initialise_game(&new_map);
	if (!check_map_name(filename))
		check = (parse_file(&new_map, filename));
	if (check == 1)
		return (0);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	data = (t_raycast *)malloc(sizeof(t_raycast));
	parse_data(data, &game, &new_map);
	init_raycast(data);
	set_hooks(data);
	mlx_loop_hook(game.mlx, engine, data);
	mlx_loop(game.mlx);
	exit_game(&game, data, &new_map);
	return (0);
}
//print_map_config(&new_map); // nur zum testen

/* void	print_map_config(t_map *map)
{
	int	i;

	i = 0;
	printf("NO: %s\n", map->textures[NO].path);
	printf("SO: %s\n", map->textures[SO].path);
	printf("WE: %s\n", map->textures[WE].path);
	printf("EA: %s\n", map->textures[EA].path);
	printf("Floor: %d,%d,%d\n", map->floor[0], map->floor[1], map->floor[2]);
	printf("Ceiling: %d,%d,%d\n\n", map->ceiling[0], map->ceiling[1],
		map->ceiling[2]);
	// ggf. Map selbst anzeigen (char **)
	while (i < map->height)
	{
		printf("%i: %s\n", i, map->grid[i]);
		i++;
	}
	printf("\n");
	printf("Map height = %i\n", map->height);
	printf("Map width = %i\n\n", map->width);
	printf("player dir: %c\n", map->player_dir);
	printf("player x: %i\n", map->player_x);
	printf("player y: %i\n", map->player_y);
} */
