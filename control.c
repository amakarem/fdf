/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:19:14 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/19 01:20:29 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	projection_switch(t_vars *vars)
{
	if (vars->screen->projection == 1)
		vars->screen->projection = 0;
	else
		vars->screen->projection = 1;
	drawimage(vars);
}

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
	if (keycode == 1)
		vars->screen->angle += 0.05;
	else if (keycode == 2)
		vars->screen->angle -= 0.05;
	else if (keycode == 124)
		vars->screen->x_offset++;
	else if (keycode == 123)
		vars->screen->x_offset--;
	else if (keycode == 126)
		vars->screen->y_offset--;
	else if (keycode == 125)
		vars->screen->y_offset++;
	else if (keycode == 75)
	{
		vars->screen->angle = M_PI / 6;
		vars->screen->projection = 0;
		vars->screen->zoom = zoomsize(vars->screen);
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
	else if (keycode == 35)
		projection_switch(vars);
	return (0);
}

int	mouse_event(int button, int x, int y, t_vars *vars)
{
	if (x <= 0 || y <= 0)
		return (0);
	if (button == 4 || button == 5)
		return (zoominout(button, vars), 0);
	if (button == 2)
		return (control(75, vars), 0);
	if ((SCREEN_WIDTH / 2) - x > 0)
		return (rotate(2, vars), 0);
	if ((SCREEN_WIDTH / 2) - x <= 0)
		return (rotate(1, vars), 0);
	return (0);
}
