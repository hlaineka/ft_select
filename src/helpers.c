/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:53:39 by helvi             #+#    #+#             */
/*   Updated: 2021/03/04 20:46:26 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_terminal *g_info;

int			ft_putc(int c)
{
	write(g_info->fd_out, &c, 1);
	return (1);
}

/*
** Checks and saves to info structure the size of the window.
*/

void		check_window_size(t_terminal *info)
{
	struct winsize	window_size;

	ioctl(info->fd_out, TIOCGWINSZ, &window_size);
	info->screenrows = window_size.ws_row;
	info->screencols = window_size.ws_col;
}

/*
** Function to clear the screen before options are printed. The cursor
** location was saved when the program started, and now we use it as the
** starting location.
*/

void		ft_clear_screen(t_terminal *info)
{
	tputs(info->cl_string, info->screenrows, &ft_putc);
}
