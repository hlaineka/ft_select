/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:03:43 by helvi             #+#    #+#             */
/*   Updated: 2021/03/03 19:24:11 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	save_cursor_position(t_option *node, t_terminal *info)
{
	node->cursorcol = info->cursorcol;
	node->cursorrow = info->cursorrow;
}

void	print_mv_cursor(char *printable, t_terminal *info)
{
	int		length;
	int		i;

	length = ft_strlen(printable);
	if (-1 != (i = ft_str_find_c(printable, '\n')))
	{
		ft_putstr_fd(printable, info->fd_out);
		info->cursorrow++;
		info->cursorcol = length - i - 1;
	}
	else if ((info->cursorcol + length) >= info->screencols)
	{
		ft_putstr_fd(printable, info->fd_out);
		ft_putstr_fd("\r\n", info->fd_out);
		info->cursorcol = length;
		info->cursorrow++;
	}
	else
	{
		ft_putstr_fd(printable, info->fd_out);
		info->cursorcol = info->cursorcol + length;
	}
}

void	move_cursor(t_option *first, t_terminal *info)
{
	t_option	*temp;

	temp = first;
	while (temp)
	{
		if (temp->cursor)
		{
			tputs(tgoto(info->cm_string, temp->cursorcol, temp->cursorrow),
				(info->screenrows - temp->cursorrow), &ft_putc);
			break ;
		}
		temp = temp->next;
	}
}
