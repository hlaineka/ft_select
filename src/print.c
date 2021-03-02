/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 11:59:24 by helvi             #+#    #+#             */
/*   Updated: 2021/03/02 21:06:11 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		print_one(t_option *printable, t_terminal *info)
{
	if ((info->cursorcol + (int)ft_strlen(printable->name) + 4) > info->screencols)
		print_mv_cursor("\r\n", info);
	print_mv_cursor("(", info);
	save_cursor_position(printable, info);
	if (printable->selected)
		print_mv_cursor("x)", info);
	else
		print_mv_cursor(" )", info);
	if (printable->cursor)
		tputs(info->us_string, 1, &ft_putc);
	if (printable->selected)
		tputs(info->mr_string, 1, &ft_putc);
	print_mv_cursor(printable->name, info);
	tputs(info->me_string, 1, &ft_putc);
	if (info->cursorcol != 0 && info->cursorcol != info->screencols)
		print_mv_cursor(" ", info);
	if (printable->cursor)
	{
		info->cursor_saved_row = printable->cursorrow;
		info->cursor_saved_col = printable->cursorcol;
	}

}

void		reset_screen(t_terminal *info)
{
	check_window_size(info);
	ft_clear_screen(info);
	info->cursorrow = 0;
	info->cursorcol = 0;
	info->cursor_saved_row = 0;
	info->cursor_saved_col = 0;
}

void		print_selections(t_terminal *info, t_option *first)
{
	t_option	*temp;
	
	temp = first;
	reset_screen(info);
	print_one(temp, info);
	temp = temp->next;
	while (temp != first)
	{
		print_one(temp, info);
		temp = temp->next;
	}
	ft_putstr_fd("\r\n", info->fd_out);
	tputs(tgoto(info->cm_string, info->cursor_saved_col, info->cursor_saved_row), info->screenrows, &ft_putc);
}