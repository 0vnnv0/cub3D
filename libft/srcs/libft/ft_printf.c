/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:06:25 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/24 12:14:34 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_format(char c, va_list args)
{
	int	count2;

	count2 = 0;
	if (c == 's')
		count2 = ft_putstr(va_arg(args, char *));
	else if (c == 'c')
		count2 = ft_putchar(va_arg(args, int));
	else if (c == 'd' || c == 'i')
		count2 = ft_putnbr(va_arg(args, int), 0);
	else if (c == 'u')
		count2 = ft_putui(va_arg(args, unsigned int), 0);
	else if (c == 'x' || c == 'X')
		count2 = ft_puthex(va_arg(args, unsigned int), c);
	else if (c == '%')
		count2 = ft_putchar('%');
	else if (c == 'p')
		count2 = ft_putpointer(va_arg(args, size_t));
	return (count2);
}

int	ft_printf(const char *str, ...)
{
	int	i;
	int	count;

	va_list(args);
	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			count = count + write(1, &str[i], 1);
		}
		else
		{
			i++;
			count = count + ft_format(str[i], args);
		}
		i++;
	}
	va_end(args);
	return (count);
}

/*int	main()
{
	char	*string = "fuckmylife";
	ft_printf("hello my name is %s\n", string);
	printf("hello my name is %s\n", string);
	
	char letter= 'u';
	ft_printf("the letter is: %c\n", letter);
	printf("the letter is: %c\n", letter);

	int num = -14857334;
	ft_printf("the int is: %i\n", num);
	printf("the int is: %i\n", num);

	unsigned int zahl = 666;
	ft_printf("the ui is: %u\n", zahl);
	printf("the ui is: %u\n", zahl);

	int hexe = 95;
	ft_printf("the hexe is: %x\n", hexe);
	printf("the hexe is: %X\n", hexe);

	void	*point;
	ft_printf("pointer: %p\n", (void *)&num);
	printf("pointer: %p\n", (void *)&num);
}*/