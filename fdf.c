/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:38:59 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/10 19:06:27 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

void	save_pixels(t_screen *screen, char *line, int v)
{
	char	**arr;
	char	**set;
	int		i[2];

	arr = ft_split(line, ' ');
	if (!arr)
		free_and_exit("Memory error", screen);
	i[0] = 0;
	while (arr[i[0]])
	{
		set = ft_split(arr[i[0]], ',');
		i[1] = ft_atoi(set[0]);
		if (set[1])
			set_pixel(screen, v, i, ft_atoi(set[1]));
		else
			set_pixel(screen, v, i, 0x90EE90);
		i[0]++;
		free_arr(set);
		if (!screen)
			free_and_exit("Memory error", screen);
	}
	free_arr(arr);
}

t_screen	*load_map(t_screen *screen, char *filename)
{
	int			fd;
	char		*line;
	int			i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "No file ", 8);
		free_and_exit(filename, screen);
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		save_pixels(screen, line, i++);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	set_vertical_neighbors(screen);
	return (screen);
}

int	close_window(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == 17)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode < 0)
		exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_screen	*screen;

	if (argc != 2)
		error_exit("Usage : ./fdf <filename> [ case_size z_size ]");
	screen = init_screen();
	if (!screen)
		error_exit("Can't allocate memory");
	load_map(screen, argv[1]);
	printpixels(screen);
	drawpixels(screen, argv[1]);
	freepixels(screen);
	return (0);
}
