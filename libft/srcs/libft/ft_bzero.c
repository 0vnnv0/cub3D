/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:30:21 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/24 12:13:03 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*string;

	string = s;
	while (n > 0)
	{
		*string = '\0';
		string++;
		n--;
	}
}

/*int	main()
{
        char    a[] = "dvbh fewjfe kwn0";
        printf("Vor dem fuellen: %s\n", a);
        ft_bzero(a, 3);
        printf("Nach dem fuellen: %s\n", a);
        return (0);
}*/
