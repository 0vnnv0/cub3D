/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:56:31 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/12 17:38:02 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putui(unsigned int nb, int count)
{
	char	c;

	if (nb >= 10)
	{
		count = ft_putui((nb / 10), count);
		count = ft_putui((nb % 10), count);
	}
	else
	{
		c = nb + 48;
		write(1, &c, 1);
		count++;
	}
	return (count);
}
