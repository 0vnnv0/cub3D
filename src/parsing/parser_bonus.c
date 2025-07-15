/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:56:14 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/09 18:23:11 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

int	process_map_line(t_map *map, char *line)
{
	check_width(map, line);
	handle_map_line(map, line);
	if (is_skippable(line))
		return (exit_with_error(map, line, "empty line found"));
	return (0);
}

int	parse_config(t_map *map, char **line, int fd)
{
	if (process_config_line(map, *line))
	{
		free(*line);
		return (1);
	}
	if (!map->map_started)
	{
		free(*line);
		*line = get_next_line(fd);
		return (2);
	}
	return (0);
}

int	validate_file(t_map *map, int fd)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!map->map_started)
		{
			ret = parse_config(map, &line, fd);
			if (ret == 1)
				return (1);
			if (ret == 2)
				continue ;
		}
		if (process_map_line(map, line))
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	normalize_map_width(map);
	if (validate_map(map))
		return (1);
	return (0);
}

int	is_empty_file(const char *filename)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read == 0)
		return (1);
	return (0);
}

int	parse_file(t_map *map, char *filename)
{
	int		fd;
	int		empty_check;

	empty_check = is_empty_file(filename);
	if (empty_check == -1)
		return (printf(RED "Error: file not found\n" RESET), 1);
	if (empty_check == 1)
		return (printf(RED "Error: empty file\n" RESET), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf(RED "Error: map couldn't open\n" RESET), 1);
	if (validate_file(map, fd) == 0)
		return (0);
	return (1);
}
