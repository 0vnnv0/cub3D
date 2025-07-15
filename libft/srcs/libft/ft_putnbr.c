/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:17:45 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/12 17:38:02 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_printchar(char c)
{
	write(1, &c, 1);
}

int	ft_putnbr(int nb, int count)
{
	long	number;

	number = nb;
	if (number == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (number < 0)
	{
		ft_printchar('-');
		number = -number;
		count++;
	}
	if (number >= 10)
	{
		count = ft_putnbr((number / 10), count);
	}
	ft_printchar((number % 10) + '0');
	count++;
	return (count);
}
