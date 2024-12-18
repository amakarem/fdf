/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:19:14 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/18 15:32:30 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoominout(int keycode, t_vars *vars)
{
	if (keycode == 69)
		vars->screen->zoom++;
	else if (keycode == 78)
		vars->screen->zoom--;
	drawimage(vars);
}

void	rotate(int keycode, t_vars *vars)
{
	if (keycode == 124)
		vars->screen->angle++;
	else if (keycode == 123)
		vars->screen->angle--;
	else if (keycode == 75)
	{
		vars->screen->angle = M_PI / 6;
		vars->screen->zoom = zoomsize(vars->screen) / 2;
	}
	drawimage(vars);
}

int	close_window(int keycode, t_vars *vars)
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
	else if (keycode == 124 || keycode == 123 || keycode == 75)
		rotate(keycode, vars);
	else
		printf("\n %d", keycode);
	return (0);
}
