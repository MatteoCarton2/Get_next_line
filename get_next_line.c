/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:56:16 by mcarton           #+#    #+#             */
/*   Updated: 2025/02/07 11:55:50 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
    int bytes_read;
    size_t i;
    size_t j;
    size_t k;
    char *buffer;     // on créer le "sceau", le buffer
    int flag; // temporaire
    char *line;
    static char *remaining;

    i = 0;
    j = 0;
    k = 0;
    flag = 0; // temporaire
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1)); // on malloc ce "sceau" avec la taille du sceau défini via BUFFER_SIZE + \0
    if (!buffer)
        return (NULL);    
    bytes_read = read(fd, buffer, BUFFER_SIZE);  // read = remplit le buffer
    //	•	fd → Le fichier à lire (le descripteur de fichier).
	//  •	buffer → Là où les données seront stockées (le sceau).
	//  •	BUFFER_SIZE → Combien d’octets on veut lire à chaque fois(la taille du sceau).
    if (bytes_read < 1)     // si c'est 0 = fin du fichier, si -1 = erreur
        return (free(buffer), NULL);
    buffer[bytes_read] = '\0'; // mettre le \0 à la position bytes_read, car c’est le nombre exact de caractères lus.
    while (buffer[i])
    {
        if(buffer[i] == '\n')
        {
            printf("Position trouvée = %zu\n", i);
            flag = 1;
            line = malloc(sizeof(char) * (i + 2));
            if (!line)
                return (free(buffer), NULL);
            while (j <= i)
            {
                line[j] = buffer[j];
                j++;
            }
            line[j] = '\0';
            remaining = malloc(sizeof(char) * ());
            if (!remaining)
                return(free(line), free(buffer), NULL);
            while (j < i)
            {
                remaining[k] = buffer[j];
                j++;
            }
            remaining[k] = '\0';
            break;
        }
        i++;
    }
    if (flag == 0)
    {
        printf("Pas de saut de ligne trouvé\n");
        line = malloc(sizeof(char) * (i + 2));
        if (!line)
            return (free(buffer), NULL);
        while (j < i)
            {
                line[j] = buffer[j];
                j++;
            }
        line[j] = '\0';
    }
    free(buffer);
    return (line);
}

#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;
    
    if (argc != 2)
        return (0);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur lors de l'open du fd\n");
        return (0);
    }
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}