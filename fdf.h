/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:03:31 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/05 21:14:43 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_pixel
{
	int		v;
	int		h;
	int		set;
	char	*color;
	struct s_pixel	*next;
}	t_pixel;

char	*get_next_line(int fd);
void	error_exit(const char *msg);
void	free_and_exit(const char *msg, t_pixel **pixels);
void	free_arr(char **str);
void	set_pixel(t_pixel **pixels, int v, int h, int set, char *color);
void	freepixels(t_pixel **pixel);
void	printpixels(t_pixel **pixel);

#endif
