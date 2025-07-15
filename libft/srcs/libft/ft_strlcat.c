/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:23:51 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/12 17:39:17 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lens;
	size_t	lend;

	lens = ft_strlen(src);
	lend = ft_strlen(dst);
	if (lend > dstsize)
		lend = dstsize;
	if (lend == dstsize)
		return (dstsize + lens);
	if (dstsize - lend > lens)
		ft_memcpy(dst + lend, src, lens + 1);
	else
	{
		ft_memcpy(dst + lend, src, dstsize - lend -1);
		dst[dstsize -1] = '\0';
	}
	return (lens + lend);
}

/*int	main()
{
	char *source = "Hi my name is";
	char *desti = "slim shady";

	printf("%zu\n", ft_strlcat(desti, source, 97));
	return (0);
}*/
