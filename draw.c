/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:44:02 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/18 18:25:15 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_delta_values(t_iso iso, t_iso iso_nxt, int *ds)
{
	ds[0] = abs(iso_nxt.x - iso.x);
	ds[1] = abs(iso_nxt.y - iso.y);
	ds[2] = -1;
	if (iso.x < iso_nxt.x)
		ds[2] = 1;
	ds[3] = -1;
	if (iso.y < iso_nxt.y)
		ds[3] = 1;
	ds[4] = ds[0] - ds[1];
}

// ds[0] dx
// ds[1] dy
// ds[2] sx
// ds[3] sy
// ds[4] err
// ds[5] e2
void	draw_line(t_data *img, t_iso iso, t_iso iso_nxt, int color)
{
	int	ds[6];

	get_delta_values(iso, iso_nxt, ds);
	while (1)
	{
		my_mlx_pixel_put(img, iso.x, iso.y, color);
		if (iso.x == iso_nxt.x && iso.y == iso_nxt.y)
			break ;
		ds[5] = ds[4] * 2;
		if (ds[5] > -ds[1])
		{
			ds[4] -= ds[1];
			iso.x += ds[2];
		}
		if (ds[5] < ds[0])
		{
			ds[4] += ds[0];
			iso.y += ds[3];
		}
	}
}

void	draw_lines_between_pixels(t_screen *screen, t_data *img)
{
	t_pixel	*pix;
	t_pixel	*nextpix;

	pix = screen->top;
	while (pix)
	{
		nextpix = screen->top;
		while (nextpix)
		{
			if (pix->x == nextpix->x && (nextpix->y - pix->y) == 1)
				draw_line(img, pix->iso, nextpix->iso, pix->color);
			if (pix->y == nextpix->y && (nextpix->x - pix->x) == 1)
				draw_line(img, pix->iso, nextpix->iso, pix->color);
			nextpix = nextpix->next;
		}
		pix = pix->next;
	}
}

void	drawimage(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	preprocess_iso(vars->screen);
	draw_lines_between_pixels(vars->screen, &img);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
}
