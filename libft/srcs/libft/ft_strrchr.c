/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:55:28 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/12 17:38:02 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			temp = (char *)&s[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (temp);
}

// int	main()
// {
// 	char *string = "teste";
// 	char *first_t = ft_strrchr(string, '\0');
// 	char *first_B = ft_strrchr(string, 'B');

// 	printf("first i can be found: %s\n", first_t);
// 	printf("first B can be found: %s\n", first_B);
// 	return (0);
// }
