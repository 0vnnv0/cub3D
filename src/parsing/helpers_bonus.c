/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:55:30 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/09 18:08:49 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus.h"

int	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

int	is_skippable(char *line)
{
	char	*trimmed;

	trimmed = trim_leading_whitespace(line);
	if (*trimmed == '\0' || *trimmed == '\n')
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

char	*correct_path(char *src)
{
	char	*dst;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(src) + 1;
	dst = malloc(len + 1);
	j = 0;
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] == ' ' || src[i] == '\t')
		i++;
	while (len > 0 && ft_isspace(src[len - 1]))
	{
		len--;
	}
	while (i < len && src[i] != '\n')
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (dst);
}

char	*trim_whitespace(char *str)
{
	int		start;
	int		end;
	int		len;
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	start = 0;
	while (str[start] == ' ' || str[start] == '\t' || str[start] == '\v'
		|| str[start] == '\f' || str[start] == '\r' || str[start] == '\0'
		|| str[start] == '\n')
		start++;
	end = len - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t'
			|| str[end] == '\v'
			|| str[end] == '\f' || str[end] == '\r' || str[end] == '\n'))
		end--;
	new = malloc(end - start + 2);
	i = 0;
	while (start <= end)
		new[i++] = str[start++];
	new[i] = '\0';
	return (new);
}

char	*trim_leading_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	return (strdup(str));
}
