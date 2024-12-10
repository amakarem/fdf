/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:12:30 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/10 18:44:49 by aelaaser         ###   ########.fr       */
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
