/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:02:36 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/31 18:27:26 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <limits.h>

static int	countdigits(int n)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
		return (11);
	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_negative(char *str, int *count, int *n)
{
	if (*n == INT_MIN)
	{
		str[10] = '8';
		*n /= 10;
		(*count)--;
	}
	str[0] = '-';
	*n = -(*n);
	(*count)--;
	return (str + 1);
}

char	*ft_itoa(int n)
{
	char	*nulled;
	char	*str;
	int		length;

	length = countdigits(n);
	nulled = malloc((length + 1) * sizeof(char));
	if (!nulled)
		return (NULL);
	nulled[length] = '\0';
	str = nulled;
	if (n < 0)
		str = ft_negative(str, &length, &n);
	while (length--)
	{
		str[length] = (n % 10) + '0';
		n /= 10;
	}
	return (nulled);
}
