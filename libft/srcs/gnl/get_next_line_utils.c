/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:36:36 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/11 14:53:16 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"
#include "../../includes/libft.h"

char	*ft_strchr_gnl(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_strlen_gnl(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *str, char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	if (!str)
	{
		str = (char *)malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (!str || !buffer)
		return (NULL);
	tmp = malloc((ft_strlen_gnl(str) + ft_strlen_gnl(buffer) + 1)
			* sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (str[++i] != '\0')
		tmp[i] = str[i];
	while (buffer[j] != '\0')
		tmp[i++] = buffer[j++];
	tmp[ft_strlen_gnl(str) + ft_strlen_gnl(buffer)] = '\0';
	free (str);
	return (tmp);
}
