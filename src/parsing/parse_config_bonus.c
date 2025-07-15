/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:40:38 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/09 18:26:40 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

int	is_config_line(const char *line)
{
	if (!ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2)
		|| !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "DO", 2)
		|| !ft_strncmp(line, "DC", 2)
		|| !ft_strncmp(line, "F", 1)
		|| !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

int	parse_config_line(t_map *map, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (store_texture_path(map, &map->textures[NO], line + 2));
	else if (!ft_strncmp(line, "SO", 2))
		return (store_texture_path(map, &map->textures[SO], line + 2));
	else if (!ft_strncmp(line, "WE", 2))
		return (store_texture_path(map, &map->textures[WE], line + 2));
	else if (!ft_strncmp(line, "EA", 2))
		return (store_texture_path(map, &map->textures[EA], line + 2));
	else if (!ft_strncmp(line, "DO", 2))
		return (store_texture_path(map, &map->textures[DO], line + 2));
	else if (!ft_strncmp(line, "DC", 2))
		return (store_texture_path(map, &map->textures[DC], line + 2));
	else if (!ft_strncmp(line, "F", 1))
		return (store_color(map, map->floor, line + 1));
	else if (!ft_strncmp(line, "C", 1))
		return (store_color(map, map->ceiling, line + 1));
	return (1);
}

int	handle_config_line(t_map *map, char *line)
{
	char	*trimmed;

	trimmed = trim_leading_whitespace(line);
	if (!is_config_line(trimmed))
		return (exit_with_error(map, trimmed, "invalid configs"));
	if (parse_config_line(map, trimmed) == 0)
	{
		if (map->config_count == 6 && map->c_set && map->f_set)
			map->header_done = 1;
	}
	else
	{
		free (trimmed);
		return (1);
	}
	free (trimmed);
	return (0);
}

int	process_config_line(t_map *map, char *line)
{
	if (is_skippable(line))
		return (0);
	if (!map->header_done)
	{
		if (handle_config_line(map, line))
			return (1);
		return (0);
	}
	map->map_started = 1;
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\0');
}
