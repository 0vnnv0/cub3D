/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:19:46 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/24 12:14:00 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tempdest;
	unsigned char	*tempsrc;

	if (!dest && !src)
		return (dest);
	tempdest = (unsigned char *) dest;
	tempsrc = (unsigned char *) src;
	if (tempdest < tempsrc)
	{
		while (n--)
			*tempdest++ = *tempsrc++;
	}
	else
	{
		tempdest += n -1;
		tempsrc += n -1;
		while (n--)
			*tempdest-- = *tempsrc--;
	}
	return (dest);
}
/*int	main()
{
	char source[] = "hello my name is";
	char destination[] = "hola mi nombre es";
	ft_memmove(destination, source, 9);

	printf("%s\n", destination);
	return (0);
}*/
