/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:12:30 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/16 18:45:52 by aelaaser         ###   ########.fr       */
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

// void	set_vertical_neighbors(t_screen *screen)
// {
// 	t_pixel	*current;
// 	t_pixel	*down_pixel;

// 	if (!screen || screen->size == 0)
// 		return ;
// 	current = screen->top;
// 	while (current != NULL)
// 	{
// 		down_pixel = screen->top;
// 		while (down_pixel != NULL)
// 		{
// 			if (down_pixel->x == current->x && down_pixel->y == current->y + 1)
// 			{
// 				current->down = down_pixel;
// 				break ;
// 			}
// 			down_pixel = down_pixel->next;
// 		}
// 		current = current->next;
// 	}
// }

void	set_pixel(t_screen *screen, int y, int hset[2], int color)
{
	t_pixel	*new_pixel;
	t_pixel	*current;

	new_pixel = malloc(sizeof(t_pixel));
	if (!new_pixel)
		free_and_exit("Memory error", screen);
	new_pixel->y = y;
	new_pixel->x = hset[0];
	new_pixel->z = hset[1];
	new_pixel->color = color;
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
		printf("\nV:%i H:%i Z:%i COLOR:%d", x->y, x->x, x->z, x->color);
		if (x->next)
			printf("-----H2:%i", x->next->x);
		if (x->down)
			printf("-----V2:%i", x->down->y);
		x = x->next;
	}
}
