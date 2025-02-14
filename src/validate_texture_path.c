/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:08:26 by mcheragh          #+#    #+#             */
/*   Updated: 2025/02/12 16:35:45 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Check if a given texture path is valid
int is_valid_texture_path(char *path)
{
	int len;
	int fd;

	if (!path || (len = ft_strlen(path)) == 0)
	{
		printf("Error: Empty texture path\n");
		return (0);
	}
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		printf("Error: Texture file must be a .xpm file\n");
		return (0);
	}
	// fd = open(path, O_RDONLY);
	// if (fd == -1)
	// {
	// 	printf("Error: Texture file %s does not exist\n", path);
	// 	return (0);
	// }
	//close(fd);
	return (1);
}


