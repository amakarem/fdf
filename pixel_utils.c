/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:12:30 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/05 21:20:53 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

t_pixel	*lastpixel(t_pixel *lst)
{
	t_pixel	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	pixeladd_back(t_pixel **pixels, t_pixel *new)
{
	t_pixel	*tmp;

	tmp = lastpixel(*pixels);
	if (tmp)
		tmp->next = new;
	else
		*pixels = new;
}

void	set_pixel(t_pixel **pixels, int v, int h, int set, char *color)
{
	t_pixel	*new_pixel;

	new_pixel = malloc(sizeof(t_pixel));
	if (!new_pixel)
		free_and_exit("Memory error", pixels);
	new_pixel->v = v;
	new_pixel->h = h;
	new_pixel->set = set;
	new_pixel->color = ft_strdup(color);
	if (!new_pixel->color)
	{
		free(new_pixel);
		free_and_exit("Memory error", pixels);
	}
	new_pixel->next = NULL;
	pixeladd_back(pixels, new_pixel);
}

void	freepixels(t_pixel **pixel)
{
	t_pixel	*tmp;

	while (*pixel)
	{
		tmp = (*pixel)->next;
		free(*pixel);
		*pixel = tmp;
	}
	free(*pixel);
	*pixel = NULL;
}

void	printpixels(t_pixel **pixel)
{
	while (*pixel)
	{
		printf("\nV:%i H:%i SET:%i COLOR:%s", (*pixel)->v, (*pixel)->h, (*pixel)->set, (*pixel)->color);
		*pixel = (*pixel)->next;
	}
}
