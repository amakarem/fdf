/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:44:02 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/12 16:35:38 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//isometric_projection
void	iso(t_pixel *pix, int *vhd, t_screen *screen)
{
	int	x_offset;
	int	y_offset;
	int	angle;
	int	zoom;

	angle = 210;
	zoom = screen->zoom;
	x_offset = (int)(SCREEN_WIDTH / 2);
	y_offset = (int)(SCREEN_HEIGHT / 2);
	vhd[0] = (pix->v - pix->h) * cos(angle) * zoom + x_offset;
	vhd[1] = ((pix->v + pix->h) * sin(angle) - pix->set) * zoom + y_offset;
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

// ds[0] dx
// ds[1] dy
// ds[2] sx
// ds[3] sy
// ds[4] err
// ds[5] e2
void	draw_line(t_data *img, int *vhd, int *vh_nxt, int color)
{
	int	ds[6];

	ds[0] = abs(vh_nxt[0] - vhd[0]);
	ds[1] = abs(vh_nxt[1] - vhd[1]);
	ds[2] = -1;
	if (vhd[0] < vh_nxt[0])
		ds[2] = 1;
	ds[3] = -1;
	if (vhd[1] < vh_nxt[1])
		ds[3] = 1;
	ds[4] = ds[0] - ds[1];
	while (1)
	{
		my_mlx_pixel_put(img, vhd[0], vhd[1], color);
		if (vhd[0] == vh_nxt[0] && vhd[1] == vh_nxt[1])
			break ;
		ds[5] = ds[4] * 2;
		if (ds[5] > -ds[1])
		{
			ds[4] -= ds[1];
			vhd[0] += ds[2];
		}
		if (ds[5] < ds[0])
		{
			ds[4] += ds[0];
			vhd[1] += ds[3];
		}
	}
}

void	draw_lines_between_pixels(t_screen *screen, t_data *img)
{
	t_pixel	*pix;
	int		vhd[2];
	int		vh_nxt[2];

	pix = screen->top;
	while (pix)
	{
		iso(pix, vhd, screen);
		if (pix->next)
		{
			iso(pix->next, vh_nxt, screen);
			draw_line(img, vhd, vh_nxt, pix->color);
		}
		if (pix->down)
		{
			iso(pix->down, vh_nxt, screen);
			draw_line(img, vhd, vh_nxt, pix->color);
		}
		pix = pix->next;
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
		iso(pix, vhd, screen);
		my_mlx_pixel_put(&img, vhd[0], vhd[1], pix->color);
		pix = pix->next;
	}
	draw_lines_between_pixels(screen, &img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, close_window, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_loop(vars.mlx);
	freepixels(screen);
}
