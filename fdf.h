/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:03:31 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/05 19:07:35 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_screen
{
	int		h;
	int		v;
	int		set;
	char	*color;
	struct s_screen	*next;
}	t_screen;