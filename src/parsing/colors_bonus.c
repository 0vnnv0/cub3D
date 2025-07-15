/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:03:44 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/09 16:56:56 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

int	duplicate_color(t_map *map, int *color)
{
	if (color == map->floor && map->f_set)
		return (exit_with_error(map, NULL, "floor color defined twice"));
	if (color == map->ceiling && map->c_set)
		return (exit_with_error(map, NULL, "ceiling color defined twice"));
	return (0);
}

void	set_color_flag(t_map *map, int *color)
{
	if (color == map->floor)
		map->f_set = 1;
	else if (color == map->ceiling)
		map->c_set = 1;
}

int	check_color(t_map *map, int rgb, char *color, int i)
{
	if (i >= 3)
		return (exit_with_error(map, NULL, "too many rgb values"));
	if (ft_isnumber(color))
		return (exit_with_error(map, NULL, "RGB contains wrong char"));
	if (rgb < 0 || rgb > 255)
		return (exit_with_error(map, NULL, "RGB out of range"));
	return (0);
}

int	process_color(char **colors, int *texture, t_map *map)
{
	int		i;
	char	*trimmed;
	char	*stripped;

	i = 0;
	while (colors[i])
	{
		trimmed = trim_leading_whitespace(colors[i]);
		if (!trimmed)
			return (exit_with_error(map, NULL, "memory allocation failed"));
		stripped = trim_whitespace(trimmed);
		free(trimmed);
		if (!stripped)
			return (exit_with_error(map, NULL, "memory allocation failed"));
		free(colors[i]);
		colors[i] = stripped;
		texture[i] = ft_atoi(colors[i]);
		if (check_color(map, texture[i], colors[i], i))
			return (1);
		i++;
	}
	return (0);
}

int	store_color(t_map *map, int *texture, char *line)
{
	char	**colors;

	colors = ft_split(line, ',');
	if (!colors)
		return (exit_with_error(map, line, "memory allocation failed"));
	if (check_following_char(map, line))
		return (cleanup_colors(colors), 1);
	if (duplicate_color(map, texture))
		return (cleanup_colors(colors), 1);
	if (process_color(colors, texture, map))
		return (cleanup_colors(colors), 1);
	set_color_flag(map, texture);
	cleanup_colors(colors);
	return (0);
}
