/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:03:31 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/06 18:39:52 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_pixel
{
	int				v;
	int				h;
	int				set;
	int				color;
	struct s_pixel	*next;
}	t_pixel;

typedef struct s_screen
{
	t_pixel	*top;
	int		size;
}	t_screen;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

char		*get_next_line(int fd);
void		error_exit(const char *msg);
void		free_and_exit(const char *msg, t_screen *scree);
void		free_arr(char **str);
t_screen	*init_screen(void);
void		set_pixel(t_screen *screen, int v, int hset[2], int color);
void		freepixels(t_screen *screen);
void		printpixels(t_screen *screen);
int			close_window(int keycode, t_vars *vars);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		drowpixels(t_screen *screen, char *title);
#endif
