/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:47:55 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/13 19:26:32 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	zoomsize(t_screen *screen)
{
	t_pixel	*x;
	int		max_v;
	int		max_h;

	x = screen->top;
	max_v = 1;
	max_h = 1;
	while (x)
	{
		if (x->y > max_v)
			max_v = x->y;
		if (x->x > max_h)
			max_h = x->x;
		x = x->next;
	}
	if (SCREEN_WIDTH > SCREEN_HEIGHT)
		return ((int)(SCREEN_WIDTH / max_h) / 4);
	return ((int)(SCREEN_HEIGHT / max_v) / 4);
}

int	hex_to_int(const char *hex_str)
{
	char	c;
	int		value;
	int		result;
	int		i;

	result = 0;
	i = 0;
	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		i = 2;
	while (hex_str[i] != '\0')
	{
		c = hex_str[i];
		value = 0;
		if (ft_isdigit(c))
			value = c - '0';
		else if (c >= 'a' && c <= 'f')
			value = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			value = c - 'A' + 10;
		else
			return (0x90EE90);
		result = result * 16 + value;
		i++;
	}
	return (result);
}
