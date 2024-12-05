/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:38:59 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/05 17:39:13 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
	int		i;

	if(argc != 2)
		error_exit("Usage : ./fdf <filename> [ case_size z_size ]");
	i = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
		write(STDERR_FILENO, "No file ", 8);
		error_exit(argv[1]);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("[%i]%s", i, line);
        free(line);
		i++;
    }
    close(fd);
    return (0);
}
