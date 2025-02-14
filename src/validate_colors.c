/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:54:21 by mcheragh          #+#    #+#             */
/*   Updated: 2025/02/10 12:38:59 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "libft.h"

void	free_two_dim(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// Validate color and return a t_color structure with RGB values
int	is_valid_color_texture(t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	if(ft_strchr(color->color_str, '/') != NULL)
	{
		color->mode = 2;
		if(!is_valid_texture_path(color->color_str))
		{
			print_error("Error: Invalid texture for floor or ceiling\n");
			return (0);
		}
		color->texture = ft_strdup(color->color_str);
	}
	else
	{
		color->mode = 1;
		rgb = ft_split(color->color_str, ',');
		if (!rgb || two_dim_len(rgb) != 3)
		{
			print_error("Error: Invalid color format. Expected R,G,B\n");
			free_two_dim(rgb);
			return (0);
		}
		if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1]) || \
			!is_valid_number(rgb[2]))
		{
			printf("Error: Color values must be numbers\n");
			free_two_dim(rgb);
			return (0);
		}
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);
		free_two_dim(rgb);
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		{
			printf("Error: Color values must be between 0 and 255\n");
			return (0);
		}
		color->r = r;
		color->g = g;
		color->b = b;
	}
	return (1);
}
