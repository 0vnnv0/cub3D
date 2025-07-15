/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:06:53 by anschmit          #+#    #+#             */
/*   Updated: 2024/04/29 14:08:11 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	uc;
	size_t			i;

	string = (unsigned char *) s;
	uc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (string[i] == uc)
			return ((void *) &string[i]);
		i++;
	}
	return (NULL);
}

/*int	main()
{
	char search[] = "Hola que pasa?";
	char *first_a = ft_memchr(search, 'a', 10);
	
	printf("first a can be found: %s\n", first_a);
	return (0);
}*/
