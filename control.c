/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:19:14 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/18 18:01:04 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoominout(int keycode, t_vars *vars)
{
	if (keycode == 69 || keycode == 4)
		vars->screen->zoom++;
	else if (keycode == 78 || keycode == 5)
		vars->screen->zoom--;
	drawimage(vars);
}

void	rotate(int keycode, t_vars *vars)
{
	if (keycode == 124 || keycode == 125)
		vars->screen->angle += 0.05;
	else if (keycode == 123 || keycode == 126)
		vars->screen->angle -= 0.05;
	else if (keycode == 75)
	{
		vars->screen->angle = M_PI / 6;
		vars->screen->zoom = zoomsize(vars->screen) / 2;
	}
	drawimage(vars);
}

int	control(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == 17 || keycode < 0)
	{
		if (keycode > 0)
		{
			freepixels(vars->screen);
			mlx_destroy_window(vars->mlx, vars->win);
		}
		exit(0);
	}
	else if (keycode == 69 || keycode == 78)
		zoominout(keycode, vars);
	else if ((keycode >= 123 && keycode <= 126) || keycode == 75)
		rotate(keycode, vars);
	else if (keycode == 1 || keycode == 2)
		printf("\n Rotate Mouse event:%d", keycode);
	else if (keycode == 4 || keycode == 5)
		printf("\n Zoom Mouse event:%d", keycode);
	else
		printf("\n %d", keycode);
	return (0);
}
