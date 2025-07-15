/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:49:29 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/12 17:38:02 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <unistd.h>

int	ft_puthexpoint(size_t nr, int count)
{
	char	*base;

	base = "0123456789abcdef";
	if (nr > 15)
	{
		count = ft_puthexpoint((nr / 16), count);
		count = ft_puthexpoint((nr % 16), count);
	}
	else
	{
		write(1, &base[nr], 1);
		count++;
	}
	return (count);
}

int	ft_putpointer(size_t pointer)
{
	int	count;

	if (!pointer)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count = ft_puthexpoint(pointer, 0);
	return (count + 2);
}
