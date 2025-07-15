/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:37:28 by anschmit          #+#    #+#             */
/*   Updated: 2024/07/24 12:22:21 by anschmit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

char	*get_next_line(int fd);
char	*ft_read(int fd, char *str);
char	*ft_getline(char *full_str);
char	*ft_getrest(char *full_str);
char	*ft_strjoin_gnl(char *str, char *buffer);
size_t	ft_strlen_gnl(char *str);
char	*ft_strchr_gnl(char *str, int c);

#endif