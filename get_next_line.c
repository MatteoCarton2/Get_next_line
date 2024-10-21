/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarton <mcarton@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:49:48 by mcarton           #+#    #+#             */
/*   Updated: 2024/10/21 22:38:47 by mcarton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			octets_lu;
	static char	*restant;

	char buffer[BUFFER_SIZE + 1];
    octets_lu = read(fd, buffer, BUFFER_SIZE);
    if (octets_lu == -1)
        return (NULL);
    buffer[octets_lu] = '\0';

}

int	main(int argc, char **argv)
{
	int fd;
	char *ligne;

	if (argc < 2)
	{
		printf("Trop peu d'arguments.\n");
		return (1);
	}
	if (argc > 2)
	{
		printf("Trop d'arguments.\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Erreur lors de l'ouverture du fichier.\n");
		return (1);
	}
	while ((ligne = get_next_line(fd)))
	{
		printf("%s", ligne);
		free(ligne);
	}
	close(fd);
	return (0);
}