/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:44:02 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/10 18:44:40 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(int x, int y, int z, int *vhd)
{
	double	angle;
	double	zoom;
	double	x_offset;
	double	y_offset;

	angle = 210;
	zoom = 8;
	x_offset = (int)(SCREEN_WIDTH / 2);
	y_offset = (int)(SCREEN_HEIGHT / 2);
	vhd[0] = (x - y) * cos(angle) * zoom + x_offset;
	vhd[1] = ((x + y) * sin(angle) - z) * zoom + y_offset;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 800 && y >= 0 && y < 600)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	drawpixels(t_screen *screen, char *title)
{
	t_vars	vars;
	t_pixel	*pix;
	t_data	img;
	int		vhd[2];

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, title);
	img.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	pix = screen->top;
	while (pix)
	{
		isometric_projection(pix->v, pix->h, pix->set, vhd);
		my_mlx_pixel_put(&img, vhd[0], vhd[1], pix->color);
		pix = pix->next;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, close_window, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx);
	freepixels(screen);
}
