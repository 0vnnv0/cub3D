/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:12:45 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/22 17:33:54 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

/*int	main()
{
	char *string = "This is a test!";
	char *first_t = ft_strchr(string, '\0');
	char *first_B = ft_strchr(string, -154);

	printf("first t can be found: %s\n", first_t);
	printf("first B can be found: %s\n", first_B);
	return (0);
}*/
