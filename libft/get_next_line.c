/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcheragh <mcheragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:24:46 by mcheragh          #+#    #+#             */
/*   Updated: 2025/02/12 16:35:10 by mcheragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Helper function to extract a line from the archive buffer
static char *line_from_archive(char *archive)
{
    int i = 0;
    char *line;

    // Check if archive is empty
    if (!archive || !archive[i])
        return NULL;

    // Find the position of the newline character, if any
    while (archive[i] && archive[i] != '\n')
        i++;

    // Allocate memory for the line (i characters + 1 for null terminator)
    line = (char *)malloc(sizeof(char) * (i + 1));
    if (!line)
        return NULL;

    // Copy characters from archive to the line
    i = 0;
    while (archive[i] && archive[i] != '\n')
    {
        line[i] = archive[i];
        i++;
    }

    // Null-terminate the line
    line[i] = '\0';

    return line;
}


// Main function to get the next line from a file descriptor
char *get_next_line(int fd)
{
    static char *archive[4096];
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    archive[fd] = read_to_archive(fd, archive[fd]);  // Read data into archive
    if (!archive[fd])  // No data to read
        return NULL;

    line = line_from_archive(archive[fd]);  // Get the line from archive
    if (!line)  // No line could be extracted
        return NULL;

    archive[fd] = update_archive(archive[fd]);  // Update the archive after extraction

    return line;
}