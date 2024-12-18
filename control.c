/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:19:14 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/18 15:14:07 by aelaaser         ###   ########.fr       */
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
