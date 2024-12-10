/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:12:30 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/10 22:23:07 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_screen	*init_screen(void)
{
	t_screen	*screen;

	screen = malloc(sizeof(t_screen));
	if (!screen)
		return (NULL);
	screen->top = NULL;
	return (screen);
}

void	set_vertical_neighbors(t_screen *screen)
{
	t_pixel	*current;
	t_pixel	*down_pixel;
	t_pixel	*row_start;

	row_start = NULL;
	if (!screen || screen->size == 0)
		return ;
	current = screen->top;
	while (current != NULL)
	{
		if (row_start == NULL || current->v != row_start->v)
			row_start = current;
		down_pixel = current->next;
		while (down_pixel != NULL)
		{
			if (down_pixel->h == current->h && down_pixel->v == current->v + 1)
			{
				current->down = down_pixel;
				break ;
			}
			down_pixel = down_pixel->next;
		}
		current = current->next;
	}
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
		return (free(new_pixel), free_and_exit("Memory error", screen));
	new_pixel->next = NULL;
	new_pixel->down = NULL;
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
