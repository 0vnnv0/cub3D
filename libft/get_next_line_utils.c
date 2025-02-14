/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsasse <lsasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:19:51 by lsasse            #+#    #+#             */
/*   Updated: 2024/06/05 10:59:56 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen2(const char *s)
{
    size_t i;
	
	i = 0;

    if (s)  // Check for NULL at the start
    {
        while (s[i])
            i++;
    }
    return i;
}

// static char *ft_strchr2(const char *s, int c)
// {
//     if (!s)  // If s is NULL, return NULL immediately
//         return NULL;

//     if (c == '\0')  // Special case for NULL-terminator
//         return (char *)&s[ft_strlen2(s)];

//     while (*s)  // Iterate through string
//     {
//         if (*s == (char)c)
//             return (char *)s;
//         s++;
//     }

//     return NULL;  // Return NULL if no match found
// }


char *ft_strjoin2(char *archive, const char *buff)
{
    size_t i = 0;
    size_t j = 0;
    char *str;

    if (!buff)
        return NULL;
    
    if (!archive)  // Initialize archive if it is NULL
    {
        archive = (char *)malloc(1 * sizeof(char));
        if (!archive)
            return NULL;
        archive[0] = '\0';
    }

    // Calculate the lengths of both strings once
    size_t archive_len = ft_strlen2(archive);
    size_t buff_len = ft_strlen2(buff);

    // Allocate memory for the new string
    str = (char *)malloc(sizeof(char) * (archive_len + buff_len + 1));
    if (!str)
    {
        free(archive);  // Ensure you free the archive memory if malloc fails
        return NULL;
    }

    // Copy characters from archive to the new string
    while (archive[i] != '\0')
    {
        str[i] = archive[i];
        i++;
    }

    // Copy characters from buff to the new string
    while (buff[j] != '\0')
    {
        str[i++] = buff[j++];
    }

    // Null-terminate the new string
    str[i] = '\0';

    // Free the old archive string
    free(archive);

    return str;
}

// Function to update the archive after reading a line
char *update_archive(char *archive)
{
    int i = 0;
    char *new_archive;

    // Check if archive is empty
    if (!archive || !archive[i])
        return NULL;

    // Find the newline character if it exists
    while (archive[i] && archive[i] != '\n')
        i++;

    // If we reached the end of the archive (no newline found), nothing to update
    if (!archive[i])
    {
        free(archive);
        return NULL;
    }

    // If there's more data after the newline, shift it
    new_archive = ft_strdup(archive + i + 1);
    free(archive);
    
    return new_archive;
}


// Function to read data into the archive buffer from the file descriptor
char *read_to_archive(int fd, char *archive)
{
    char *buffer;
    int bytes_read;

    // Allocate a buffer to read from the file descriptor
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);

    // Read data from the file descriptor into the buffer
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    if (bytes_read <= 0) // Error or end of file
    {
        free(buffer);
        return (archive);
    }

    buffer[bytes_read] = '\0';  // Null-terminate the buffer

    // If no previous data exists, just set archive to the new buffer
    if (!archive)
    {
        archive = ft_strdup(buffer);
    }
    else
    {
        // Otherwise, append the new data to the archive
        char *new_archive = ft_strjoin(archive, buffer);
        free(archive);
        archive = new_archive;
    }

    free(buffer);  // Free the temporary buffer
    return (archive);
}
