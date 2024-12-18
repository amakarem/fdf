/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:38:59 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/18 15:16:53 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

void	save_pixels(t_screen *screen, char *line, int y)
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
			set_pixel(screen, y, i, hex_to_int(set[1]));
		else
			set_pixel(screen, y, i, 0x90EE90);
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
	screen->zoom = zoomsize(screen) / 2;
	return (screen);
}

void	drawpixels(t_screen *screen, char *title)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, title);
	vars.screen = screen;
	drawimage(&vars);
	mlx_key_hook(vars.win, close_window, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx);
	freepixels(screen);
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
	screen->angle = M_PI / 6;
	drawpixels(screen, argv[1]);
	freepixels(screen);
	return (0);
}
