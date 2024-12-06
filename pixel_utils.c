/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:12:30 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/06 19:44:50 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_screen	*init_screen(void)
{
	t_screen	*screen;

	screen = malloc(sizeof(t_screen));
	if (!screen)
		return (NULL);
	screen->top = NULL;
	return (screen);
}

void	set_pixel(t_screen *screen, int v, int hset[2], int color)
{
	t_pixel	*new_pixel;
	t_pixel	*current;

	new_pixel = malloc(sizeof(t_pixel));
	if (!new_pixel)
		free_and_exit("Memory error", screen);
	new_pixel->v = v;
	new_pixel->h = hset[0];
	new_pixel->set = hset[1];
	new_pixel->color = color - 0;
	if (!new_pixel->color)
	{
		return (free(new_pixel), free_and_exit("Memory error", screen));
	}
	new_pixel->next = NULL;
	if (screen->size == 0)
		screen->top = new_pixel;
	else
	{
		current = screen->top;
		while (current->next != NULL)
			current = current->next;
		current->next = new_pixel;
	}
	screen->size++;
}

void	freepixels(t_screen *screen)
{
	t_pixel	*tmp;

	while (screen->top)
	{
		tmp = screen->top;
		screen->top = tmp->next;
		free(tmp);
	}
	free(screen);
}

void	printpixels(t_screen *screen)
{
	t_pixel	*x;

	x = screen->top;
	while (x)
	{
		printf("\nV:%i H:%i SET:%i COLOR:%d", x->v, x->h, x->set, x->color);
		x = x->next;
	}
}

void	drowpixels(t_screen *screen, char *title)
{
	t_vars	vars;
	t_pixel	*pix;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, title);
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	pix = screen->top;
	while (pix)
	{
		//mlx_pixel_put(&vars.mlx, vars.win, pix->v, pix->h, pix->color);
		my_mlx_pixel_put(&img, pix->v, pix->h, 0x00FF0000);
		mlx_put_image_to_window(vars.mlx, vars.win, img.img, pix->v, pix->h);
		pix = pix->next;
	}
	mlx_key_hook(vars.win, close_window, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx);
	freepixels(screen);
}
