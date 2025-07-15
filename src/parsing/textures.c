/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:55:54 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/09 16:59:38 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_following_char(t_map *map, char *line)
{
	if (*line == '\n' || *line == '\0')
		return (exit_with_error(map, line, "texture/color is missing"));
	if (*line != ' ' && *line != '	')
		return (exit_with_error(map, line, "texture/color key is wrong"));
	return (0);
}

int	store_texture_path(t_map *map, t_texture *texture, char *line)
{
	int		len;
	char	*clean;

	if (check_following_char(map, line))
		return (1);
	clean = correct_path(line);
	if (!clean)
		return (1);
	len = ft_strlen(clean);
	if (len < 5)
		return (exit_with_error(map, clean, "texture not valid"));
	if (clean[len - 4] != '.' || clean[len - 3] != 'x'
		|| clean[len - 2] != 'p' || clean[len - 1] != 'm')
		return (exit_with_error(map, clean, "wrong texture format"));
	if (texture->path != NULL)
		return (exit_with_error(map, clean, "too many textures"));
	texture->path = ft_strdup(clean);
	map->config_count++;
	if (open(clean, O_RDONLY) < 0)
		return (exit_with_error(map, clean, "texture can't open"));
	free(clean);
	return (0);
}

void	render_test(t_map *map)
{
	mlx_put_image_to_window(
		map->mlx,
		map->win,
		map->textures[NO].img,
		0, 0);
}

void	load_all_textures(t_map *map, t_pro *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		map->textures[i].img = mlx_xpm_file_to_image(
				game->mlx,
				map->textures[i]. path,
				&map->textures[i].width,
				&map->textures[i].height);
		if (!map->textures[i].img)
		{
			printf(RED "Error: Failed to load texture\n" RESET);
			exit (1);
		}
		map->textures[i].addr = mlx_get_data_addr(
				map->textures[i].img,
				&map->textures[i].bits_per_pixel,
				&map->textures[i].line_length,
				&map->textures[i].endian);
		i++;
	}
}
