/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:31:38 by anschmit          #+#    #+#             */
/*   Updated: 2024/08/09 17:20:53 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

long	ft_atoi(const char *str)
{
	long	nbr;
	long	sign;

	nbr = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * sign);
}

/*#include <stdio.h>
#include <stdlib.h>
int	main()
{
	char *zahl = "  -+845h43";
	printf("%d\n", ft_atoi(zahl));
	printf("%d\n", atoi(zahl));
	return(0);
}*/
