/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:38:59 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/05 21:13:16 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

void	save_pixels(t_pixel **pixels, char *line, int v)
{
	char	**arr;
	char	**set;
	int		i;

	arr = ft_split(line, ' ');
	if (!arr)
		free_and_exit("Memory error", pixels);
	i = 0;
	while (arr[i])
	{
		set = ft_split(arr[i], ',');
		if (set[1])
			set_pixel(pixels, v, i++ , ft_atoi(set[0]), set[1]);
		else
			set_pixel(pixels, v, i++ , ft_atoi(set[0]), "FFFFFF");
		free_arr(set);
		if (!pixels)
			free_and_exit("Memory error", pixels);
	}
	free_arr(arr);
}

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
	int		i;
	t_pixel	**pixels;

	pixels = malloc(sizeof(t_pixel *));
	if (!pixels)
		return (-1);
	if(argc != 2)
		error_exit("Usage : ./fdf <filename> [ case_size z_size ]");
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
		write(STDERR_FILENO, "No file ", 8);
		error_exit(argv[1]);
    }
	i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
		save_pixels(pixels, line, i);
        free(line);
		i++;
    }
    close(fd);
	printpixels(pixels);
	freepixels(pixels);
    return (0);
}
