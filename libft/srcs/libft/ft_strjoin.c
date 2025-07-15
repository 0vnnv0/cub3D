/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lea <lea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:15:46 by anschmit          #+#    #+#             */
/*   Updated: 2025/07/11 14:55:25 by lea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*new;
	size_t		i;
	size_t		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * (sizeof(char)));
	if (!new)
		return (NULL);
	while (s1[i] != '\0')
		new[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		new[j++] = s2[i++];
	new[j] = 0;
	return (new);
}

/*int	main()
{
	char *str1;
	char *str2;

	str1 = "hello, it's me";
	str2 = "I was wondering if after all these years you'd like to meet.";

	printf("%s\n", ft_strjoin(str1, str2));
	return (0);
}*/
