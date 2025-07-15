/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:38:53 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/12 17:38:02 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	new = malloc((end - start) + 2);
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1 + start, (end - start) + 2);
	return (new);
}

/*int	main()
{
	char *main = "yerBadummreyr";
	char *trim = "yer";
	
	printf("%s\n", ft_strtrim(main, trim));
	return (0);
} */