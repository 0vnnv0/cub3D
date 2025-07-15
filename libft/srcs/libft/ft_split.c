/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:33:11 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/12 17:45:38 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	ft_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i +1] == c || s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

static int	ft_allocation(char **splits, const char *s, char c, int words)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (s[end])
	{
		if (s[end] == c || s[end] == 0)
			start = end + 1;
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == 0))
		{
			splits[words] = malloc(sizeof(char) * (end - start + 2));
			if (!splits[words])
			{
				while (words--)
					free(splits[words]);
				return (0);
			}
			ft_strlcpy(splits[words], &s[start], (end - start + 2));
			words++;
		}
		end++;
	}
	splits[words] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!strings)
		return (NULL);
	if (!ft_allocation(strings, s, c, 0))
	{
		free(strings);
		return (NULL);
	}
	return (strings);
}
